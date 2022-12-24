#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include "Absyn.H"
#include "Skeleton.C"
#include "Common.cpp"
#include "TypeVisitor.cpp"

class FourValueTranslatorVisitor : public Skeleton {
private:
    Program *program;
    std::ofstream output_file;
    int next_t_var_number = 0;
    int next_t_block_number = 0;

    Ident current_decl_type;
    Ident current_operator;
    Ident result; // register or constant

    int current_call = 0;
    std::map<int, Ident> call_to_args_string;

    std::vector<CVar *> dummy_vector_CVar = std::vector<CVar *>();
    std::vector<CClass *> dummy_vector_CClass = std::vector<CClass *>();
    std::vector<CFun *> dummy_vector_CFun = std::vector<CFun *>();
    Type_Visitor *typeVisitor = new Type_Visitor(dummy_vector_CClass, dummy_vector_CVar, dummy_vector_CFun);

public:
    explicit FourValueTranslatorVisitor(Program *program, const std::filesystem::path &file_path) : program(program) {
        output_file.open(file_path);
        if (!output_file.is_open()) {
            std::cerr << "can't open output file" << std::endl;
            exit(1);
        }
    }

    Ident next_t_var() {
        next_t_var_number++;
        return std::string("_t" + std::to_string(next_t_var_number));
    }

    void close() {
        output_file.close();
    }

    void emitRaw(std::string content) {
        output_file << content;
    }

    void emitLine(std::string content) {
        output_file << "\t" + content + "\n";
    }

    void visitFnDef(FnDef *fnDef) override {
        next_t_var_number = 0;
        next_t_block_number = 0;

        emitRaw(fnDef->ident_ + ":\n");
        fnDef->block_->accept(this);
        emitRaw("\n");
    }

    void visitBStmt(BStmt *stmt) override {} // TODO

    void visitDecl(Decl *stmt) override {
        current_decl_type = typeVisitor->getType(stmt->type_)->name;
        stmt->listitem_->accept(this);
    }

    void visitNoInit(NoInit *stmt) override {
        if (current_decl_type == "string") {
            emitLine(stmt->ident_ + " := \"\"");
        } else {
            emitLine(stmt->ident_ + " := 0");
        }
    }

    void visitInit(Init *stmt) override {
        stmt->expr_->accept(this); // sets result (register or constant)
        emitLine(stmt->ident_ + " := " + result);
    }

    void visitAss(Ass *stmt) override {
        stmt->expr_1->accept(this);
        Ident lhs = result;
        stmt->expr_2->accept(this);
        emitLine(lhs + " := " + result);
    }

    void visitIncr(Incr *stmt) override {
        stmt->expr_->accept(this);
        emitLine(result + " ++");
    }

    void visitDecr(Decr *stmt) override {
        stmt->expr_->accept(this);
        emitLine(result + " --");
    }

    void visitRet(Ret *stmt) override {
        stmt->expr_->accept(this);
        emitLine("return " + result);
    }

    void visitVRet(VRet *stmt) override {
        emitLine("return");
    }

    void visitCond(Cond *stmt) override {} // todo

    void visitCondElse(CondElse *stmt) override {} // todo

    void visitWhile(While *stmt) override {} // todo

    void visitForEach(ForEach *stmt) override {} // todo

    void visitSExp(SExp *stmt) override {
        stmt->expr_->accept(this); // if function/method, this will emit the call, else do nothing
        if (result.substr(0, 5) == "_call") {
            emitLine(result);
        }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////

    void visitCFunction(CFunction *expr) override {
        current_call++;
        expr->listexpr_->accept(this);

        result = "_call " + expr->ident_ + call_to_args_string[current_call];
        call_to_args_string.erase(current_call);

        current_call--;
    }

    void visitListExpr(ListExpr *listExpr) override {
        for (auto i = listExpr->begin(); i != listExpr->end(); ++i) {
            (*i)->accept(this);

            if (current_call > 0) {
                auto t_var = next_t_var();
                emitLine(t_var + " := " + result);
                call_to_args_string[current_call] += " " + t_var;
            }
        }
    }

    void visitEVar(EVar *expr) override {
        result = expr->ident_;
    }

    void visitEBracketVar(EBracketVar *expr) override {
        result = expr->ident_;
    }

//    void visitEComplex(EComplex *expr) override {} // todo teraz tylko CFunction więc jest git, potem rozwinąć

    void visitENullCast(ENullCast *expr) override {} // todo

    void visitELitInt(ELitInt *expr) override {
        result = std::to_string(expr->integer_);
    }

    void visitELitTrue(ELitTrue *expr) override {
        result = "1";
    }

    void visitELitFalse(ELitFalse *expr) override {
        result = "0";
    }

    void visitEString(EString *expr) override {
        result = expr->string_;
    }

    void visitNeg(Neg *expr) override {
        expr->expr_->accept(this);
        Ident t_var = next_t_var();
        emitLine(t_var + " := - " + result);
        result = t_var;
    }

    void visitNot(Not *expr) override {
        expr->expr_->accept(this);
        Ident t_var = next_t_var();
        emitLine(t_var + " := ! " + result);
        result = t_var;
    }

    void visitEMul(EMul *expr) override {
        expr->mulop_->accept(this);
        visitBinOpp(expr->expr_1, expr->expr_2);
    }

    void visitEAdd(EAdd *expr) override {
        expr->addop_->accept(this);
        visitBinOpp(expr->expr_1, expr->expr_2);
    }

    void visitERel(ERel *expr) override {
        expr->relop_->accept(this);
        visitBinOpp(expr->expr_1, expr->expr_2);
    }

    void visitEAnd(EAnd *expr) override {
        current_operator = " && ";
        visitBinOpp(expr->expr_1, expr->expr_2);
    }

    void visitEOr(EOr *expr) override {
        current_operator = " || ";
        visitBinOpp(expr->expr_1, expr->expr_2);
    }

    void visitBinOpp(Expr *e1, Expr *e2) {
        Ident operator_ = current_operator;
        e1->accept(this);
        Ident left = result;
        e2->accept(this);
        Ident right = result;

        Ident t_var = next_t_var();
        emitLine(t_var + " := " + left + operator_ + right);
        result = t_var;
    }

    void visitPlus(Plus *op) override { current_operator = " + "; }

    void visitMinus(Minus *op) override { current_operator = " - "; }

    void visitTimes(Times *op) override { current_operator = " * "; }

    void visitDiv(Div *op) override { current_operator = " / "; }

    void visitMod(Mod *op) override { current_operator = " % "; }

    void visitLTH(LTH *op) override { current_operator = " < "; }

    void visitLE(LE *op) override { current_operator = " <= "; }

    void visitGTH(GTH *op) override { current_operator = " > "; }

    void visitGE(GE *op) override { current_operator = " >= "; }

    void visitEQU(EQU *op) override { current_operator = " == "; }

    void visitNE(NE *op) override { current_operator = " != "; }

};