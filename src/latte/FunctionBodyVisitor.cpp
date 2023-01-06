#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Common.cpp"
#include "TypeVisitor.cpp"

class Function_Body_Visitor : public Skeleton {
public:
    std::vector<CClass *> &defined_classes;
    std::vector<CFun *> &defined_global_functions;

    std::vector<CVar *> defined_variables;
    std::map<Ident, int> variable_to_depth;
    int current_depth;
    bool can_declare = true;

    CFun *current_function; // or method, whatever
    CClass *current_class;
    CType *current_type;

    bool always_returning;

    explicit Function_Body_Visitor(std::vector<CFun *> &defined_global_functions,
                                   std::vector<CClass *> &defined_classes)
            : defined_global_functions(defined_global_functions), defined_classes(defined_classes) {}

    CVar *findVar(Ident name, int line_number, int char_number) {
        for (auto def: defined_variables) {
            if (def->name == name) return def;
        }
        throwError(line_number, char_number, "undefined variable \"" + name + "\"");
        return nullptr;
    }

    void findFun(Ident name) {
        for (auto def: defined_global_functions) {
            if (def->name == name) {
                current_function = def;
                break;
            }
        }
        if (current_function == nullptr) myExit(16); // should never happen
    }

    void findMethod(Ident name) {
        for (auto def: current_class->methods) {
            if (def->name == name) {
                current_function = def;
                break;
            }
        }
        if (current_function == nullptr) myExit(17); // should never happen
    }

    void findClass(Ident name) {
        for (auto def: defined_classes) {
            if (def->name == name) {
                current_class = def;
                break;
            }
        }
        if (current_class == nullptr) myExit(18); // should never happen
    }

    void visitClassDef(ClassDef *class_def) override {
        current_class = nullptr;
        findClass(class_def->ident_);
        class_def->listclassmember_->accept(this);
    };

    void visitClassExtendDef(ClassExtendDef *class_def) override {
        current_class = nullptr;
        findClass(class_def->ident_1);
        class_def->listclassmember_->accept(this);
    };

    void visitAttrMember(AttrMember *attr_member) override {}

    void visitMethodMember(MethodMember *method) override {
        current_function = nullptr;
        findMethod(method->ident_);

        current_depth = -1; // to make first block depth 0
        defined_variables.clear();
        variable_to_depth.clear();
        for (auto arg: current_function->args) { defined_variables.push_back(arg); }
        for (auto attr: current_class->attributes) {
            bool already_defined = false;
            for (auto arg: current_function->args) {
                if (arg->name == attr->name) {
                    already_defined = true;
                    break;
                }
            }
            // function arguments are more important than attributes
            if (!already_defined)defined_variables.push_back(attr);
        }
        for (auto var: defined_variables) {
            variable_to_depth[var->name] = 0;
        }
        always_returning = false;

        method->block_->accept(this);
        if (current_function->return_type->name != "void" && !always_returning) {
            throwError(method->line_number, method->char_number,
                       "method \"" + current_function->name + "\" can end without returning a value");
        }
    }

    void visitFnDef(FnDef *fn_def) override {
        current_function = nullptr;
        current_class = nullptr;
        findFun(fn_def->ident_);

        current_depth = -1; // to make first block depth 0
        defined_variables.clear();
        variable_to_depth.clear();
        for (auto arg: current_function->args) { defined_variables.push_back(arg); }
        for (auto var: defined_variables) {
            variable_to_depth[var->name] = 0;
        }

        always_returning = false;

        fn_def->block_->accept(this);
        if (current_function->return_type->name != "void" && !always_returning) {
            throwError(fn_def->line_number, fn_def->char_number,
                       "function \"" + current_function->name + "\" can end without returning a value");
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////

    void visitBlk(Blk *block) override {
        auto backup_variables = defined_variables;
        auto backup_variable_depth_map = variable_to_depth;

        auto depth_before = current_depth;
        current_depth++;
        block->liststmt_->accept(this);
        current_depth = depth_before;

        defined_variables = backup_variables;
        variable_to_depth = backup_variable_depth_map;
    }

    void visitBStmt(BStmt *stmt) override {
        can_declare = true;
        stmt->block_->accept(this);
    }

    void visitListStmt(ListStmt *list_stmt) override {
        for (ListStmt::iterator stmt = list_stmt->begin(); stmt != list_stmt->end(); ++stmt) {
            (*stmt)->accept(this);
        }
    }

    void visitDecl(Decl *stmt) override {
        if (!can_declare)
            throwError(stmt->line_number, stmt->char_number, "cannot declare variable in blockless cond statement");

        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        current_type = typeVisitor->getType(stmt->type_);
        if (current_type->name == "void")
            throwError(stmt->line_number, stmt->char_number, "cannot declare void type variable");
        delete (typeVisitor);

        stmt->listitem_->accept(this);
    }

    CType *defineOrRedefineVariable(Ident name, int line_number, int char_number) {
        // nullptr if first definition, type of overwritten variable if redefining
        CType *overwritten_type = nullptr;
        for (int i = 0; i < defined_variables.size(); i++) {
            auto existing_name = defined_variables.at(i)->name;
            if (existing_name == name) {
                if (variable_to_depth[existing_name] < current_depth) {
                    overwritten_type = defined_variables.at(i)->type;
                    defined_variables.erase(defined_variables.begin() + i);
                    break;
                } else {
                    throwError(line_number, char_number, "redefinition of variable on same depth");
                }
            }
        }
        defined_variables.push_back(new CVar(name, current_type));
        variable_to_depth[name] = current_depth;

        return overwritten_type;
    }

    void visitNoInit(NoInit *no_init) override {
        defineOrRedefineVariable(no_init->ident_, no_init->line_number, no_init->char_number);
    }

    void visitInit(Init *init) override {
        CType *redefined_var_type = defineOrRedefineVariable(init->ident_, init->line_number, init->char_number);

        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto expr_type = typeVisitor->getExprType(init->expr_, init->ident_, redefined_var_type);

        if (current_type->is_array != expr_type->is_array ||
            (current_type->name != expr_type->name &&
             !isDescendantOf(current_type->name, expr_type->name, defined_classes))) {
            delete (typeVisitor);

            throwError(init->line_number, init->char_number,
                       "initialization expression of different type than declared");
        }
        delete (typeVisitor);
    }

    void visitAss(Ass *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);

        auto type_1 = typeVisitor->getExprType(stmt->expr_1);
        auto type_2 = typeVisitor->getExprType(stmt->expr_2);

        if (type_1->is_array != type_2->is_array ||
            (type_1->name != type_2->name && !isDescendantOf(type_1->name, type_2->name, defined_classes))) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number,
                       "assignment expression of different type than variable");
        }

        delete (typeVisitor);
    }

    void visitIncr(Incr *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "int" || !type->is_not_array()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number,
                       "can only increment integers");
        }
        delete (typeVisitor);
    }

    void visitDecr(Decr *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "int" || !type->is_not_array()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number,
                       "can only increment integers");
        }
        delete (typeVisitor);
    }

    void visitSExp(SExp *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        int error_calls_before = typeVisitor->error_function_calls;

        auto type = typeVisitor->getExprType(stmt->expr_);
        if (typeVisitor->error_function_calls > error_calls_before)
            always_returning = true;

        delete (typeVisitor);
    }

    void visitVRet(VRet *stmt) override {
        if (current_function->return_type->name != "void")
            throwError(stmt->line_number, stmt->char_number, "invalid return type");

        always_returning = true;
    }

    void visitRet(Ret *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);

        if (type->is_array != current_function->return_type->is_array ||
            (type->name != current_function->return_type->name &&
             !isDescendantOf(current_function->return_type->name, type->name, defined_classes))) {
            delete (typeVisitor);

            throwError(stmt->line_number, stmt->char_number, "invalid return type");
        }

        delete (typeVisitor);

        always_returning = true;
    }

    void visitWhile(While *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "boolean" || !type->is_not_array()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number, "loop condition must be boolean");
        }
        delete (typeVisitor);

        can_declare = false;
        bool always_returning_backup = always_returning;
        stmt->stmt_->accept(this);
        bool if_true_always_returning = always_returning;
        can_declare = true;

        always_returning = always_returning_backup ||
                           (if_true_always_returning && stmt->expr_->isAlwaysTrue());
    }


    void visitForEach(ForEach *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        CVar *array = findVar(stmt->ident_2, stmt->line_number, stmt->char_number);
        if (!array->type->is_array) {
            throwError(stmt->line_number, stmt->char_number, "cannot iterate over non-array");
        }

        auto iterator_type = typeVisitor->getType(stmt->typename_);
        if (iterator_type->is_array || iterator_type->name != array->type->name) {
            throwError(stmt->line_number, stmt->char_number, "invalid iterator type");
        }

        auto backup_variables = defined_variables;
        auto backup_variable_depth_map = variable_to_depth;

        current_type = iterator_type;

        current_depth++;
        defineOrRedefineVariable(stmt->ident_1, stmt->line_number, stmt->char_number);
        current_depth--;

        stmt->stmt_->accept(this);

        defined_variables = backup_variables;
        variable_to_depth = backup_variable_depth_map;
    }

    void visitCond(Cond *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "boolean" || !type->is_not_array()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number, "condition must be boolean");
        }
        delete (typeVisitor);

        can_declare = false;
        bool always_returning_backup = always_returning;
        stmt->stmt_->accept(this);
        bool if_true_always_returning = always_returning;
        can_declare = true;

        always_returning = always_returning_backup ||
                           (if_true_always_returning && stmt->expr_->isAlwaysTrue());
    }

    void visitCondElse(CondElse *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "boolean" || !type->is_not_array()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number, "condition must be boolean");
        }
        delete (typeVisitor);

        can_declare = false;
        bool always_returning_backup = always_returning;
//        always_returning = false;
        stmt->stmt_1->accept(this);
        bool if_true_always_returning = always_returning;

        can_declare = false;
//        always_returning = false;
        stmt->stmt_2->accept(this);
        bool if_false_always_returning = always_returning;
        can_declare = true;

        always_returning = always_returning_backup ||
                           (if_true_always_returning && if_false_always_returning) ||
                           (if_true_always_returning && stmt->expr_->isAlwaysTrue()) ||
                           (if_false_always_returning && stmt->expr_->isAlwaysFalse());
    }
};