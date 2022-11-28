#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"

class Type_Visitor : public Skeleton {
public:
    std::vector<CClass *> defined_classes; // todo te defined rzeczy mógłby dostawać referencje bo i tak ich nie zmienia
    std::vector<CVar *> defined_variables;
    std::vector<CFun *> defined_global_functions;

    CType *current_type = nullptr;
    std::vector<CVar *> current_call_arguments = std::vector<CVar *>();
    Ident new_object_type;
    bool is_accessing_member = false;

    explicit Type_Visitor(std::vector<CClass *> defined_classes, std::vector<CVar *> defined_variables,
                          std::vector<CFun *> defined_global_functions)
            : defined_classes(defined_classes), defined_variables(defined_variables),
              defined_global_functions(defined_global_functions) {}

    CType *getType(Type *t) {
        t->accept(this);
        return current_type;
    }

    void visitInt(Int *t) override { current_type = new CType("int", std::vector<int>()); }

    void visitStr(Str *t) override { current_type = new CType("string", std::vector<int>()); }

    void visitBool(Bool *t) override { current_type = new CType("boolean", std::vector<int>()); }

    void visitVoid(Void *t) override { current_type = new CType("void", std::vector<int>()); }

    CClass *getClass(Ident name, int line_number, int char_number) {
        for (auto def: defined_classes) {
            if (def->name == name)
                return def;
        }

        throwError(line_number, char_number, "undefined class \"" + name + "\"");
        return nullptr;
    }

    void visitClass(Class *t) override {
        getClass(t->ident_, t->line_number, t->char_number);

        current_type = new CType(t->ident_, std::vector<int>());
    }

    void visitArr(Arr *t) override {
        t->arrtype_->accept(this);
        auto arrtype = current_type;
        auto dim_count = t->listarrdimtype_->size();
        current_type = new CType(arrtype->name, std::vector<int>(dim_count, -1));
        // -1 is special value = uninitialized size, but marks that dimension exists
    }

    CType *getArrayType(ArrType *t) {
        t->accept(this);
        return current_type;
    }

    void visitIntArrType(IntArrType *t) override { current_type = new CType("int", std::vector<int>()); }

    void visitStrArrType(StrArrType *t) override { current_type = new CType("string", std::vector<int>()); }

    void visitBoolArrType(BoolArrType *t) override { current_type = new CType("boolean", std::vector<int>()); }

    void visitClassArrType(ClassArrType *t) override {
        bool defined = false;
        for (auto def: defined_classes) {
            if (def->name == t->ident_) {
                defined = true;
            }
        }
        if (!defined) {
            throwError(t->line_number, t->char_number, "undefined class \"" + t->ident_ + "\"");
        }

        current_type = new CType(t->ident_, std::vector<int>());
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
            for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i) {
                (*i)->accept(this);
                if (*current_type != *(current_call_arguments[0]->type)) {
                    throwError((*i)->line_number, (*i)->char_number, "invalid argument type");
                }
                current_call_arguments.erase(current_call_arguments.begin());
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
        current_type = new CType(e->ident_, std::vector<int>());
    }

    void visitELitInt(ELitInt *e) override { current_type = new CType("int", std::vector<int>()); }

    void visitELitTrue(ELitTrue *e) override { current_type = new CType("boolean", std::vector<int>()); }

    void visitELitFalse(ELitFalse *e) override { current_type = new CType("boolean", std::vector<int>()); }

    void visitEString(EString *e) override { current_type = new CType("string", std::vector<int>()); }

    void visitNeg(Neg *e) override {
        e->expr_->accept(this);
        if (current_type->name != "int")
            throwError(e->line_number, e->char_number, "negation of non-integer");

        current_type = new CType("int", std::vector<int>());
    }

    void visitNot(Not *e) override {
        e->expr_->accept(this);
        if (current_type->name != "boolean")
            throwError(e->line_number, e->char_number, "'not' of non-boolean");

        current_type = new CType("boolean", std::vector<int>());
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
                std::vector<int>()
        );
    }

    void visitEMul(EMul *e) override {
        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             std::vector < Ident > {"int"}, false);
    }

    void visitEAdd(EAdd *e) override {
        visitBinaryOperation(e->expr_1, e->expr_2, e->line_number, e->char_number,
                             std::vector < Ident > {"int", "string"}, false);
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

        if (e_complex->listcomplexpart_->empty()) {
            if (!new_object_type.empty()) {
                if (!isBasicType(new_object_type))
                    current_type = new CType(new_object_type, std::vector<int>());
                else
                    throwError(e_complex->line_number, e_complex->char_number, "can't 'new' basic non-array type");
                new_object_type = "";
            }
        } else {
            e_complex->listcomplexpart_->accept(this);
        }

        if (current_method != nullptr)
            throwError(e_complex->line_number, e_complex->char_number, "method member accessed without calling");
        if (is_accessing_member)
            throwError(e_complex->line_number, e_complex->char_number, "invalid syntax, can't end with '.'");
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

    void visitCMember(CMember *c) override { // a.b
        CType *atype = find_var(c->ident_1, c->line_number, c->char_number);
        if (isBasicType(atype->name)) {
            if (atype->array_dims.empty()) // not an array
                throwError(c->line_number, c->char_number, "attempted basic type member access");

            if (c->ident_2 != "length")
                throwError(c->line_number, c->char_number, "only member of array type is 'length'");

            // special case - basic type array length
            current_type = new CType("int", std::vector<int>());
            return;
        }

        if (!atype->array_dims.empty()) {
            if (c->ident_2 == "length") {
                current_type = new CType("int", std::vector<int>());
                return;
            }
            throwError(c->line_number, c->char_number, "only member of array type is 'length'");
        }

        for (auto def: defined_classes) {
            if (atype->name == def->name) { // found class "a"
                for (auto attribute: def->attributes) {
                    if (c->ident_2 == attribute->name) { // found attribute "b"
                        current_type = attribute->type;
                        return;
                    }
                }
                for (auto method: def->methods) {
                    if (c->ident_2 == method->name && !isBuiltInFunction(c->ident_2)) { // found method "b"
                        current_method = method;
                        return;
                    }
                }

                throwError(c->line_number, c->char_number,
                           "class \"" + atype->name + "\" has no member \"" + c->ident_2 + "\"");
            }
        }
        throwError(c->line_number, c->char_number, "undefined class \"" + atype->name + "\"");

    }

    //int a[11][22][33][44]
    // a[1] --- int [22][33][44]
    // a[1][2][3] --- int [44]
    // a[1][2][3][4] = int

    void visitListDimDef(ListDimDef *list_dim_def) override {
        for (ListDimDef::iterator i = list_dim_def->begin(); i != list_dim_def->end(); ++i) {
            (*i)->accept(this);
            if (current_type->name != "int" || !current_type->array_dims.empty())
                throwError((*i)->line_number, (*i)->char_number, "array size must be integer");
        }
    }

    void visitCArray(CArray *c) override { // a[1][2]
        CType *atype = find_var(c->ident_, c->line_number, c->char_number);
        if (atype->array_dims.empty())
            throwError(c->line_number, c->char_number,
                       "attempted array element access on non-array");

        if (atype->array_dims.size() < c->listdimdef_->size())
            throwError(c->line_number, c->char_number,
                       "array does not have enough dimensions");

        c->listdimdef_->accept(this); // make sure sizes are ints

        std::vector<int> dims;
        dims.insert(dims.end(), atype->array_dims.begin(), atype->array_dims.end());
        for (int i = 0; i < c->listdimdef_->size(); i++) {
            dims.erase(dims.begin());
        }

        current_type = new CType(atype->name, dims);
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

    void visitNewObject(NewObject *c) override { // new <class> / new int[14][2] / new <class>[14][2]
        auto type = getArrayType(c->arrtype_);
        if (!isBasicType(type->name)) {
            getClass(type->name, c->line_number, c->line_number); // make sure class exists
        }
        new_object_type = type->name;
    }

    void visitArrElement(ArrElement *p) override {
        if (current_method != nullptr)
            throwError(p->line_number, p->char_number, "method member accessed without calling");

        if (is_accessing_member)
            throwError(p->line_number, p->char_number, "invalid member access");

        auto array_type = current_type;
        p->listdimdef_->accept(this); // make sure sizes are ints
        if (!new_object_type.empty()) { // initializing array
            current_type = new CType(new_object_type, std::vector<int>(p->listdimdef_->size(), -1));
            new_object_type = "";
        } else { // accessing array
            std::cout << "AAAAAAAAAAAAAAAAAAa\n";
            if (array_type->array_dims.empty())
                throwError(p->line_number, p->char_number, "attempted array element access on non-array");

            if (array_type->array_dims.size() < p->listdimdef_->size())
                throwError(p->line_number, p->char_number, "array does not have enough dimensions");

            std::vector<int> dims;
            dims.insert(dims.end(), array_type->array_dims.begin(), array_type->array_dims.end());
            for (int i = 0; i < p->listdimdef_->size(); i++) {
                dims.erase(dims.begin());
            }

            current_type = new CType(array_type->name, dims);
        }
    }

    void visitMethod(Method *p) override {
        if (current_method == nullptr)
            throwError(p->line_number, p->char_number, "invalid call");

        if (!new_object_type.empty()) {
            if (!isBasicType(new_object_type))
                current_type = new CType(new_object_type, std::vector<int>());
            else
                throwError(p->line_number, p->char_number, "can't 'new' basic non-array type");
            new_object_type = "";
        } // raczej nigdy sie nie stanie

        if (is_accessing_member) // raczej nigdy sie nie stanie
            throwError(p->line_number, p->char_number, "invalid member access");

        current_call_arguments = current_method->args;
        if (current_call_arguments.size() != p->listexpr_->size())
            throwError(p->line_number, p->char_number,
                       "invalid argument count");

        p->listexpr_->accept(this); // check arguments

        current_type = current_method->return_type;
        current_method = nullptr;
    }

    void visitVariable(Variable *p) override { // a.b also, we are in b
        if (current_method != nullptr)
            throwError(p->line_number, p->char_number, "method member accessed without calling");

        if (!new_object_type.empty()) {
            if (!isBasicType(new_object_type))
                current_type = new CType(new_object_type, std::vector<int>());
            else
                throwError(p->line_number, p->char_number, "can't 'new' basic non-array type");
            new_object_type = "";
        }

        if (!is_accessing_member)
            throwError(p->line_number, p->char_number, "invalid member access");

        is_accessing_member = false;

        if (isBasicType(current_type->name)) {
            if (current_type->array_dims.empty()) // not an array
                throwError(p->line_number, p->char_number, "attempted basic type member access");

            if (p->ident_ != "length")
                throwError(p->line_number, p->char_number, "only member of array type is 'length'");

            // special case - basic type array length
            current_type = new CType("int", std::vector<int>());
            return;
        }

        if (!current_type->array_dims.empty()) {
            if (p->ident_ == "length") {
                current_type = new CType("int", std::vector<int>());
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

    void visitMemberAccess(MemberAccess *p) override {
        if (current_method != nullptr)
            throwError(p->line_number, p->char_number, "method member accessed without calling");

        if (!new_object_type.empty()) {
            if (!isBasicType(new_object_type))
                current_type = new CType(new_object_type, std::vector<int>());
            else
                throwError(p->line_number, p->char_number, "can't 'new' basic non-array type");
            new_object_type = "";
        }

        is_accessing_member = true;
    }
};