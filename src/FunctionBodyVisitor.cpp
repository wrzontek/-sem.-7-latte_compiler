#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Common.cpp"
#include "TypeVisitor.cpp"

class Function_Body_Visitor : public Skeleton {
public:
    std::vector<CClass *> &defined_classes; // todo tego nie zmienia
    std::vector<CFun *> &defined_global_functions; // tego nie zmienia

    std::vector<CVar *> defined_variables;
    std::map<Ident, int> variable_to_depth;
    int current_depth;

    CFun *current_function; // or method, whatever
    CClass *current_class;
    CType *current_type;

    int paths;
    int returning_paths;
    bool current_path_already_returned;

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
        if (current_function == nullptr) exit(1); // should never happen
    }

    void findMethod(Ident name) {
        for (auto def: current_class->methods) {
            if (def->name == name) {
                current_function = def;
                break;
            }
        }
        if (current_function == nullptr) exit(1); // should never happen
    }

    void findClass(Ident name) {
        for (auto def: defined_classes) {
            if (def->name == name) {
                current_class = def;
                break;
            }
        }
        if (current_class == nullptr) exit(1); // should never happen
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
        findFun(method->ident_);

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

        paths = 1;
        returning_paths = 0;
        current_path_already_returned = false;

        method->block_->accept(this);
        if (current_function->return_type->name != "void" && paths != returning_paths) {
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

        paths = 1;
        returning_paths = 0;
        current_path_already_returned = false;

        fn_def->block_->accept(this);
        if (current_function->return_type->name != "void" && paths != returning_paths) {
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
        stmt->block_->accept(this);
    }

    void visitListStmt(ListStmt *list_stmt) override {
        for (ListStmt::iterator stmt = list_stmt->begin(); stmt != list_stmt->end(); ++stmt) {
            (*stmt)->accept(this);
            if (paths == returning_paths) current_path_already_returned = true;
        }
    }

    void visitDecl(Decl *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        current_type = typeVisitor->getType(stmt->type_);
        if (current_type->name == "void")
            throwError(stmt->line_number, stmt->char_number, "cannot declare void type variable");
        delete (typeVisitor);

        stmt->listitem_->accept(this);
    }

    void defineOrRedefineVariable(Ident name, int line_number, int char_number) {
        for (int i = 0; i < defined_variables.size(); i++) {
            auto existing_name = defined_variables.at(i)->name;
            if (existing_name == name) {
                if (variable_to_depth[existing_name] < current_depth) {
                    defined_variables.erase(defined_variables.begin() + i);
                    break;
                } else {
                    throwError(line_number, char_number, "redefinition of variable on same depth");
                }
            }
        }
        defined_variables.push_back(new CVar(name, current_type));
    }

    void visitNoInit(NoInit *no_init) override {
        defineOrRedefineVariable(no_init->ident_, no_init->line_number, no_init->char_number);
    }

    void visitInit(Init *init) override {
        defineOrRedefineVariable(init->ident_, init->line_number, init->char_number);

        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);

        if (*current_type != *(typeVisitor->getExprType(init->expr_))) {
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
        if (*type_1 != *type_2) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number,
                       "assignment expression of different type than variable");
        }

        delete (typeVisitor);
    }

    void visitIncr(Incr *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "int" || !type->array_dims.empty()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number,
                       "can only increment integers");
        }
        delete (typeVisitor);
    }

    void visitDecr(Decr *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "int" || !type->array_dims.empty()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number,
                       "can only increment integers");
        }
        delete (typeVisitor);
    }

    void visitSExp(SExp *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        // TODO może tylko void może być?
//        if (type->name != "int" || !type->array_dims.empty()) {
//            delete (typeVisitor);
//            throwError(stmt->line_number, stmt->char_number,
//                       "can only increment integers");
//        }
        delete (typeVisitor);
    }

    void visitVRet(VRet *stmt) override {
        if (current_function->return_type->name != "void")
            throwError(stmt->line_number, stmt->char_number, "invalid return type");

        current_path_already_returned = true;
        returning_paths++;
    }

    void visitRet(Ret *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (*type != *current_function->return_type) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number, "invalid return type");
        }
        delete (typeVisitor);

        current_path_already_returned = true;
        returning_paths++;
    }

    void visitWhile(While *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        auto type = typeVisitor->getExprType(stmt->expr_);
        if (type->name != "boolean" || !type->array_dims.empty()) {
            delete (typeVisitor);
            throwError(stmt->line_number, stmt->char_number, "loop condition must be boolean");
        }
        delete (typeVisitor);

        stmt->stmt_->accept(this);
    }


    void visitForEach(ForEach *stmt) override {
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables, defined_global_functions);
        CVar *array = findVar(stmt->ident_2, stmt->line_number, stmt->char_number);
        if (array->type->array_dims.empty()) {
            throwError(stmt->line_number, stmt->char_number, "cannot iterate over non-array");
        }

        auto iterator_type = typeVisitor->getType(stmt->type_);
        if (!iterator_type->array_dims.empty() || iterator_type->name != array->type->name) {
            throwError(stmt->line_number, stmt->char_number, "invalid iterator type");
        }

    }


    // todo Cond, CondElse, While, ForEach

};