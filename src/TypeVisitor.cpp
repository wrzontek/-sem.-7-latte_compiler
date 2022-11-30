#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"

class Type_Visitor : public Skeleton {
public:
    std::vector<CClass *> &defined_classes;
    std::vector<CVar *> &defined_variables;
    std::vector<CFun *> &defined_global_functions;

    CType *current_type = nullptr;
    std::vector<CVar *> current_call_arguments = std::vector<CVar *>();

    explicit Type_Visitor(std::vector<CClass *> &defined_classes, std::vector<CVar *> &defined_variables,
                          std::vector<CFun *> &defined_global_functions)
            : defined_classes(defined_classes), defined_variables(defined_variables),
              defined_global_functions(defined_global_functions) {}

    CType *getType(Type *t) {
        t->accept(this);
        return current_type;
    }

    CType *getType(TypeName *t) {
        t->accept(this);
        return current_type;
    }

    void visitInt(Int *t) override { current_type = new CType("int", false); }

    void visitStr(Str *t) override { current_type = new CType("string", false); }

    void visitBool(Bool *t) override { current_type = new CType("boolean", false); }

    void visitVoid(Void *t) override { current_type = new CType("void", false); }

    void visitClass(Class *t) override {
        current_type = new CType(t->ident_, false);
    }

    CClass *getClass(Ident name, int line_number, int char_number) {
        for (auto def: defined_classes) {
            if (def->name == name)
                return def;
        }

        throwError(line_number, char_number, "undefined class \"" + name + "\"");
        return nullptr;
    }

    void visitArr(Arr *t) override {
        t->typename_->accept(this);
        current_type = new CType(current_type->name, true);
    }

    CType *getTypeNameType(TypeName *t) {
        t->accept(this);
        return current_type;
    }

    CType *getExprType(Expr *e) {
        e->accept(this);
        return current_type;
    }

    void visitVar(Ident name, int line_number, int char_number) {
        for (auto def: defined_variables) {
            if (def->name == name) {
                current_type = def->type;
                return;
            }
        }
        throwError(line_number, char_number, "undefined variable \"" + name + "\"");
    }

    void visitListExpr(ListExpr *list_expr) override {
        if (!current_call_arguments.empty()) {
            auto arguments_backup = current_call_arguments;
            for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i) {
                (*i)->accept(this);

                if (current_type->is_array != arguments_backup[0]->type->is_array ||
                    (current_type->name != arguments_backup[0]->type->name &&
                     !isDescendantOf(arguments_backup[0]->type->name, current_type->name, defined_classes))) {
                    throwError((*i)->line_number, (*i)->char_number, "invalid argument type");
                }
                arguments_backup.erase(arguments_backup.begin());
            }
        } else {
            for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i) {
                (*i)->accept(this);
            }
        }
    }

    void visitEVar(EVar *var) override { visitVar(var->ident_, var->line_number, var->char_number); }

    void visitEBracketVar(EBracketVar *var) override { visitVar(var->ident_, var->line_number, var->char_number); }

    void visitENullCast(ENullCast *e) override {
        current_type = new CType(e->ident_, false);
    }

    void visitELitInt(ELitInt *e) override { current_type = new CType("int", false); }

    void visitELitTrue(ELitTrue *e) override { current_type = new CType("boolean", false); }

    void visitELitFalse(ELitFalse *e) override { current_type = new CType("boolean", false); }

    void visitEString(EString *e) override { current_type = new CType("string", false); }

    void visitNeg(Neg *e) override {
        e->expr_->accept(this);
        if (current_type->name != "int")
            throwError(e->line_number, e->char_number, "negation of non-integer");

        current_type = new CType("int", false);
    }

    void visitNot(Not *e) override {
        e->expr_->accept(this);
        if (current_type->name != "boolean")
            throwError(e->line_number, e->char_number, "'not' of non-boolean");

        current_type = new CType("boolean", false);
    }

    void visitBinaryOperation(Expr *e1, Expr *e2, int line_number, int char_number,
                              std::vector <Ident> valid_types, bool is_rel) {
        e1->accept(this);
        auto e1_type = current_type->name;
        bool is_valid_type = false;
        for (auto t: valid_types) {
            if (t == e1_type) {
                is_valid_type = true;
                break;
            }
        }
        if (!is_valid_type && !isBasicType(e1_type)) { // e1_type is an object of a class
            for (auto valid_type: valid_types)
                if (valid_type == "<CLASS>") is_valid_type = true;
        }

        if (!is_valid_type)
            throwError(line_number, char_number, "binary operation on invalid types");

        e2->accept(this);
        if (current_type->name != e1_type)
            throwError(line_number, char_number, "binary operation on non-matching types");

        current_type = new CType(
                is_rel ? "boolean" : e1_type,
                false
        );
    }

    void visitEMul(EMul *e) override {
        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             std::vector < Ident > {"int"}, false);
    }

    void visitEAdd(EAdd *e) override {
        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             e->addop_->allowed_types(), false);
    }

    void visitERel(ERel *e) override {
        auto valid_types = e->relop_->allowed_types();

        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             valid_types, true);
    }

    void visitEAnd(EAnd *e) override {
        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             std::vector < Ident > {"boolean"}, false);
    }

    void visitEOr(EOr *e) override {
        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             std::vector < Ident > {"boolean"}, false);
    }

    /////////////////////////////////////////////////////////////

    CFun *current_method = nullptr;

    void visitEComplex(EComplex *e_complex) override {
        e_complex->complexstart_->accept(this);
        e_complex->listcomplexpart_->accept(this);

        if (current_method != nullptr)
            throwError(e_complex->line_number, e_complex->char_number, "method member accessed without calling");
    }

    CType *find_var(Ident name, int line_number, int char_number) {
        CType *type = nullptr;
        for (auto def: defined_variables) {
            if (name == def->name) {
                type = def->type;
                break;
            }
        }
        if (type == nullptr) throwError(line_number, char_number, "undefined variable \"" + name + "\"");
        return type;
    }

    CFun *find_fun(Ident name, int line_number, int char_number) {
        for (auto def: defined_global_functions) {
            if (name == def->name) {
                return def;
            }
        }
        throwError(line_number, char_number, "undefined function \"" + name + "\"");
        return nullptr;
    }

    void memberCommon(Ident name, Ident member_name, int line_number, int char_number) {
        CType *atype = find_var(name, line_number, char_number);
        if (isBasicType(atype->name)) {
            if (atype->is_not_array()) // not an array
                throwError(line_number, char_number, "attempted basic type member access");

            if (member_name != "length")
                throwError(line_number, char_number, "only member of array type is 'length'");

            // special case - basic type array length
            current_type = new CType("int", false);
            return;
        }

        if (!atype->is_not_array()) {
            if (member_name == "length") {
                current_type = new CType("int", false);
                return;
            }
            throwError(line_number, char_number, "only member of array type is 'length'");
        }

        for (auto def: defined_classes) {
            if (atype->name == def->name) { // found class "a"
                for (auto attribute: def->attributes) {
                    if (member_name == attribute->name) { // found attribute "b"
                        current_type = attribute->type;
                        return;
                    }
                }
                for (auto method: def->methods) {
                    if (member_name == method->name && !isBuiltInFunction(member_name)) { // found method "b"
                        current_method = method;
                        return;
                    }
                }

                throwError(line_number, char_number,
                           "class \"" + atype->name + "\" has no member \"" + member_name + "\"");
            }
        }
        throwError(line_number, char_number, "undefined class \"" + atype->name + "\"");

    }

    void visitCMember(CMember *c) override { // a.b
        memberCommon(c->ident_1, c->ident_2, c->line_number, c->char_number);
    }

    void visitCMemberB(CMemberB *c) override { // (a).b
        memberCommon(c->ident_1, c->ident_2, c->line_number, c->char_number);
    }

    void arrayCommon(Ident name, Expr *expr, int line_number, int char_number, int e_line_number, int e_char_number) {
        CType *atype = find_var(name, line_number, char_number);
        if (atype->is_not_array())
            throwError(line_number, char_number,
                       "attempted array element access on non-array");

        expr->accept(this);
        if (current_type->name != "int" || !current_type->is_not_array())
            throwError(e_line_number, e_char_number, "array size must be integer");

        current_type = new CType(atype->name, false);
    }

    void visitCArray(CArray *c) override { // a[1]
        auto type = getTypeNameType(c->typename_);
        if (isBasicType(type->name))
            throwError(c->line_number, c->char_number, "");

        arrayCommon(type->name, c->expr_, c->line_number, c->char_number, c->expr_->line_number, c->expr_->char_number);
    }

    void visitCArrayB(CArrayB *c) override { // (a)[1]
        arrayCommon(c->ident_, c->expr_, c->line_number, c->char_number, c->expr_->line_number, c->expr_->char_number);
    }

    void visitCFunction(CFunction *c) override { // function(123, "arg1", a)
        CFun *fun = find_fun(c->ident_, c->line_number, c->char_number);

        current_call_arguments = fun->args;
        if (current_call_arguments.size() != c->listexpr_->size())
            throwError(c->line_number, c->char_number,
                       "invalid argument count");

        c->listexpr_->accept(this); // check arguments

        current_type = fun->return_type;
    }

    void visitNewObject(NewObject *c) override { // new <class> / new int
        if (!isBasicType(c->ident_)) {
            if (c->ident_ == "void")
                throwError(c->line_number, c->char_number, "cannot create void-type object or array");

            getClass(c->ident_, c->line_number, c->line_number); // make sure class exists
        } else {
            throwError(c->line_number, c->char_number, "can't 'new' basic non-array type");
        }

        current_type = new CType(c->ident_, false);
    }

    void visitNewArray(NewArray *c) override { // (new <class>[1]) / (new int[1])
        auto type = getTypeNameType(c->typename_);
        if (!isBasicType(type->name)) {
            getClass(type->name, c->line_number, c->line_number); // make sure class exists
        }

        if (type->name == "void")
            throwError(c->line_number, c->char_number, "cannot create void-type object or array");

        c->expr_->accept(this);
        if (current_type->name != "int" || !current_type->is_not_array())
            throwError(c->expr_->line_number, c->expr_->char_number, "array size must be integer");

        current_type = new CType(type->name, true);
    }

    void visitArrElement(ArrElement *p) override {
        if (current_method != nullptr)
            throwError(p->line_number, p->char_number, "method member accessed without calling");

        auto array_type = current_type;

        p->expr_->accept(this);
        if (current_type->name != "int" || !current_type->is_not_array())
            throwError(p->expr_->line_number, p->expr_->char_number, "array size must be integer");

        // accessing array
        if (array_type->is_not_array())
            throwError(p->line_number, p->char_number, "attempted array element access on non-array");

        current_type = new CType(array_type->name, false);
    }

    void visitMethod(Method *p) override {
        if (current_method == nullptr)
            throwError(p->line_number, p->char_number, "invalid call");

        current_call_arguments = current_method->args;
        if (current_call_arguments.size() != p->listexpr_->size())
            throwError(p->line_number, p->char_number,
                       "invalid argument count");

        auto return_type = current_method->return_type;
        current_method = nullptr;
        p->listexpr_->accept(this); // check arguments

        current_type = return_type;
    }

    void visitVariable(Variable *p) override { // a.b also, we are in b
        if (current_method != nullptr)
            throwError(p->line_number, p->char_number, "method member accessed without calling");

        if (isBasicType(current_type->name)) {
            if (current_type->is_not_array()) // not an array
                throwError(p->line_number, p->char_number, "attempted basic type member access");

            if (p->ident_ != "length")
                throwError(p->line_number, p->char_number, "only member of array type is 'length'");

            // special case - basic type array length
            current_type = new CType("int", false);
            return;
        }

        if (!current_type->is_not_array()) {
            if (p->ident_ == "length") {
                current_type = new CType("int", false);
                return;
            }
            throwError(p->line_number, p->char_number, "only member of array type is 'length'");
        }

        for (auto def: defined_classes) {
            if (current_type->name == def->name) { // found class "a"
                for (auto attribute: def->attributes) {
                    if (p->ident_ == attribute->name) { // found attribute "b"
                        current_type = attribute->type;
                        return;
                    }
                }
                for (auto method: def->methods) {
                    if (p->ident_ == method->name && !isBuiltInFunction(p->ident_)) { // found method "b"
                        current_method = method;
                        return;
                    }
                }

                throwError(p->line_number, p->char_number,
                           "class \"" + current_type->name + "\" has no member \"" + p->ident_ + "\"");
            }
        }

        throwError(p->line_number, p->char_number, "INTERNAL: undefined class \"" + current_type->name + "\"");
    }
};