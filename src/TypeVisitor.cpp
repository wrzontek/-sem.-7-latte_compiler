#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"

class Type_Visitor : public Skeleton {
public:
    std::vector<CClass *> &defined_classes;
    std::vector<CVar *> &defined_variables;
    std::vector<CFun *> &defined_functions;
    CType *current_type = nullptr;

    explicit Type_Visitor(std::vector<CClass *> &defined_classes, std::vector<CVar *> &defined_variables,
                          std::vector<CFun *> &defined_functions)
            : defined_classes(defined_classes), defined_variables(defined_variables),
              defined_functions(defined_functions) {}

    CType *getType(Type *t) {
        t->accept(this);
        return current_type;
    }

    void visitInt(Int *t) override { current_type = new CType("int", std::vector<int>()); }

    void visitStr(Str *t) override { current_type = new CType("string", std::vector<int>()); }

    void visitBool(Bool *t) override { current_type = new CType("boolean", std::vector<int>()); }

    void visitVoid(Void *t) override { current_type = new CType("void", std::vector<int>()); }

    void visitClass(Class *t) override {
        bool defined = false;
        for (auto def: defined_classes) {
            if (def->name == t->ident_) {
                defined = true;
            }
        }
        if (!defined) {
            throwError(t->line_number, t->char_number, "undefined class");
        }

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
        if (!is_valid_type)
            throwError(line_number, char_number, "binary operation on invalid types");

        e2->accept(this);
        if (current_type->name != e1_type)
            throwError(line_number, char_number, "binary operation on invalid types");

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
        if (e_complex->complexstart_) e_complex->complexstart_->accept(this);
        if (e_complex->listcomplexpart_) e_complex->listcomplexpart_->accept(this);
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
        CFun *fun = nullptr;
        for (auto def: defined_functions) {
            if (name == def->name) {
                fun = def;
                break;
            }
        }
        if (fun == nullptr) throwError(line_number, char_number, "undefined function \"" + name + "\"");
        return fun;
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

        for (auto def: defined_classes) {
            std::cout << "AAAAA " + def->name << std::endl;
            if (atype->name == def->name) { // found class "a"
                for (auto attribute: def->attributes) {
                    std::cout << "BBBB " + attribute->name << std::endl;
                    if (c->ident_2 == attribute->name) { // found attribute "b"
                        current_type = attribute->type; // next token must be ArrElement or MemberAccess
                        return;
                    }
                }
                for (auto method: def->methods) {
                    if (c->ident_2 == method->name && !isBuiltInFunction(c->ident_2)) { // found method "b"
                        current_method = method; // next token must be Method and contain proper args
                        return;
                    }
                }
            }

            throwError(c->line_number, c->char_number,
                       "class \"" + atype->name + "\" has no member \"" + c->ident_2 + "\"");
        }
        throwError(c->line_number, c->char_number, "undefined class \"" + atype->name + "\"");

    }

    //int a[11][22][33][44]
    // a[1] --- int [22][33][44]
    // a[1][2][3] --- int [44]
    // a[1][2][3][4] = int

    void visitCArray(CArray *c) override { // a[1][2]
        CType *atype = find_var(c->ident_, c->line_number, c->char_number);
        if (atype->array_dims.empty())
            throwError(c->line_number, c->char_number,
                       "attempted array element access on non-array");

        if (atype->array_dims.size() < c->listdimdef_->size())
            throwError(c->line_number, c->char_number,
                       "array does not have enough dimensions");

        std::vector<int> dims;
        dims.insert(dims.end(), atype->array_dims.begin(), atype->array_dims.end());
        for (int i = 0; i < c->listdimdef_->size(); i++) {
            dims.erase(dims.begin());
        }

        current_type = new CType(atype->name, dims);
    }

    void visitCFunction(CFunction *c) override { // function(123)
        CFun *fun = find_fun(c->ident_, c->line_number, c->char_number);

    }


    // TODO pozostałe ComplexStart, ComplexPart
};