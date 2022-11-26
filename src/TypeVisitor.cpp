#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"

class Type_Visitor : public Skeleton {
public:
    std::vector<CClass *> &defined_classes;
    std::vector<CVar *> &defined_variables;
    CType *current_type = nullptr;

    explicit Type_Visitor(std::vector<CClass *> &defined_classes, std::vector<CVar *> &defined_variables)
            : defined_classes(defined_classes), defined_variables(defined_variables) {}

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
            throwError(t->line_number, t->char_number, "undefined class");
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

    void visitEComplex(EComplex *e) override {
        // TODO
    }

};