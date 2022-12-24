#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <set>
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
    Ident result; // register or constant
//    Ident result_type; // int, string, bool

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

    void visitDecr(Incr *stmt) override {
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
        stmt->expr->accept(this); // if function/method, this will emit the call, else do nothing
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////

    void visitEVar(EVar *expr) override {
        result = expr->ident_;
    }

    void visitEBracketVar(EVar *expr) override {
        result = expr->ident_;
    }

    void visitEComplex(EComplex *expr) override {
        emitLine("TODO COMPLEX");
    }

    void visitENullCast(ENullCast *expr) override {} // todo

    void visitELitInt(ELitInt *expr) override {
        result = expr->integer_;
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
        result = "- " + result; // TODO czy to dziala dobrze przy np zanawiasowanych negacjach nastackowanych?
    }

    void visitNot(Not *expr) override {
        expr->expr_->accept(this);
        result = "! " + result; // TODO czy to dziala dobrze przy np zanawiasowanych ! nastackowanych?
    }

    // TODO reszta
};