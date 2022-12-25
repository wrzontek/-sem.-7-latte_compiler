#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include "Absyn.H"
#include "Skeleton.C"
#include "Common.cpp"
#include "TypeVisitor.cpp"

class BoolLazyEvalChecker : public Skeleton {
public:
    bool is_lazy_eval = false;

    explicit BoolLazyEvalChecker() {}

    void visitEAnd(EAnd *e) override {
        is_lazy_eval = true;
    }

    void visitEOr(EOr *e) override {
        is_lazy_eval = true;
    }

    void visitCFunction(CFunction *e) override {} // do not consider function arguments, they are handled separately

};

struct labels_struct {
    Ident label_true;
    Ident label_false;
    Ident label_end;
};

class FourValueTranslatorVisitor : public Skeleton {
private:
    Program *program;
    std::ofstream output_file;
    int next_t_var_number = 0;
    int next_t_block_number = 0;
    int next_cond_label_number = 0;

    Ident current_decl_type;
    Ident current_operator;
    Ident result; // register or constant
    bool is_result_atomic;

    Ident next_block_name;

    bool using_lazy_eval = false;
    labels_struct labels;

    int current_call = 0;
    std::map<int, Ident> call_to_args_string;

    Expr *e_1;
    Expr *e_2;

    std::vector<CVar *> dummy_vector_CVar = std::vector<CVar *>();
    std::vector<CClass *> dummy_vector_CClass = std::vector<CClass *>();
    std::vector<CFun *> dummy_vector_CFun = std::vector<CFun *>();
    Type_Visitor *typeVisitor = new Type_Visitor(dummy_vector_CClass, dummy_vector_CVar, dummy_vector_CFun);
    BoolLazyEvalChecker *boolLazyEvalChecker = new BoolLazyEvalChecker();

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

    Ident next_t_block() {
        next_t_block_number++;
        return std::string("_t" + std::to_string(next_t_block_number));
    }

    Ident gen_next_cond_label() {
        next_cond_label_number++;
        return std::string("_l" + std::to_string(next_cond_label_number));
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
        using_lazy_eval = false;
        next_t_var_number = 0;
        next_t_block_number = 0;

        emitRaw(fnDef->ident_ + ":\n");
        fnDef->block_->accept(this);
        emitRaw("\n");
    }

    void visitDecl(Decl *stmt) override {
        using_lazy_eval = false;
        current_decl_type = typeVisitor->getType(stmt->type_)->name;
        stmt->listitem_->accept(this);
    }

    void visitNoInit(NoInit *stmt) override {
        using_lazy_eval = false;
        if (current_decl_type == "string") {
            emitLine(stmt->ident_ + " := \"\"");
        } else {
            emitLine(stmt->ident_ + " := 0");
        }
    }

    void lazyEval(Ident result_register, Expr *expr) {
        auto labels_backup = labels;

        labels.label_true = "_true" + gen_next_cond_label();
        labels.label_false = "_false" + gen_next_cond_label();

        auto labels_backup_2 = labels;
        expr->accept(this);

        labels = labels_backup_2;
        labels.label_end = "_end" + gen_next_cond_label();

        emitRaw(labels.label_true + ":\n");
        if (!result_register.empty()) emitLine(result_register + " := 1");
        emitLine("_goto " + labels.label_end);
        emitRaw(labels.label_false + ":\n");
        if (!result_register.empty()) emitLine(result_register + " := 0");
        emitLine("_goto " + labels.label_end);
        emitRaw(labels.label_end + ":\n");

        labels = labels_backup;
    }

    void visitInit(Init *stmt) override {
        boolLazyEvalChecker->is_lazy_eval = false;
        stmt->expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (!using_lazy_eval) {
            stmt->expr_->accept(this);
            emitLine(stmt->ident_ + " := " + result);
        } else {
            lazyEval(stmt->ident_, stmt->expr_);
            using_lazy_eval = false;
        }
    }

    void visitAss(Ass *stmt) override {
        using_lazy_eval = false;
        stmt->expr_1->accept(this);
        Ident lhs = result;

        boolLazyEvalChecker->is_lazy_eval = false;
        stmt->expr_2->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (!using_lazy_eval) {
            stmt->expr_2->accept(this);
            emitLine(lhs + " := " + result);
        } else {
            lazyEval(lhs, stmt->expr_2);
            using_lazy_eval = false;
        }
    }

    void visitSExp(SExp *stmt) override {
        boolLazyEvalChecker->is_lazy_eval = false;
        stmt->expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (!using_lazy_eval) {
            stmt->expr_->accept(this); // if function/method, this will emit the call, else do nothing
            if (result.substr(0, 5) == "_call") { // todo???
                emitLine(result);
            }
        } else {
            lazyEval("", stmt->expr_);
            using_lazy_eval = false;
        }
    }

    void visitIncr(Incr *stmt) override {
        using_lazy_eval = false;
        stmt->expr_->accept(this);
        emitLine(result + " ++");
    }

    void visitDecr(Decr *stmt) override {
        using_lazy_eval = false;
        stmt->expr_->accept(this);
        emitLine(result + " --");
    }

    void visitRet(Ret *stmt) override {
        using_lazy_eval = false;
        stmt->expr_->accept(this);
        emitLine("return " + result);
    }

    void visitVRet(VRet *stmt) override {
        using_lazy_eval = false;
        emitLine("return");
    }

    void visitBStmt(BStmt *stmt) override { // todo musi się zachowyać mądrzej przy ifie/pętlach
        using_lazy_eval = false;
        Ident t_block;
        if (next_block_name.empty()) {
            t_block = next_t_block();
        } else {
            t_block = next_block_name;
        }

        auto after_t_block = "_after" + t_block;
        if (next_block_name.empty()) {
            emitLine("_goto " + t_block);
        }
        next_block_name = "";
        emitRaw(t_block + ":\n");

        stmt->block_->accept(this);

        emitLine("_goto " + after_t_block);
        emitRaw(after_t_block + ":\n");
    }

    void visitCond(Cond *stmt) override {
        Ident cond_atom;
        boolLazyEvalChecker->is_lazy_eval = false;
        stmt->expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (!using_lazy_eval) {
            stmt->expr_->accept(this);
            if (is_result_atomic) {
                cond_atom = result;
            } else {
                cond_atom = next_t_var();
                emitLine(cond_atom + " := " + result);
            }
        } else {
            cond_atom = next_t_var();
            lazyEval(cond_atom, stmt->expr_);
            using_lazy_eval = false;
        }

        if (stmt->stmt_->isBlock()) {
            next_t_block_number++;
            next_block_name = "_if_true_" + std::to_string(next_t_block_number);
            auto after_block = "_after" + next_block_name;

            emitLine("if " + cond_atom + " then goto " + next_block_name + " else goto " + after_block);
//            emitRaw(next_block_name + ":\n");
            stmt->stmt_->accept(this);
        } else {
            next_t_block_number++;
            auto if_true = "_if_true_" + std::to_string(next_t_block_number);
            auto end_if = "_end_if_" + std::to_string(next_t_block_number);
            emitLine("if " + cond_atom + " then goto " + if_true + " else goto " + end_if);
            emitRaw(if_true + ":\n");

            stmt->stmt_->accept(this);
            emitLine("_goto " + end_if);
            emitRaw(end_if + ":\n");
        }
    }

    void visitCondElse(CondElse *stmt) override {
        using_lazy_eval = false;

    } // todo

    void visitWhile(While *stmt) override {
        using_lazy_eval = false;

    } // todo

    void visitForEach(ForEach *stmt) override {
        using_lazy_eval = false;

    } // todo

///////////////////////////////////////////////////////////////////////////////////////////////////////////

    void visitCFunction(CFunction *expr) override {
        auto labels_backup = labels;
        current_call++;
        expr->listexpr_->accept(this);

        result = "_call " + expr->ident_ + call_to_args_string[current_call];
        call_to_args_string.erase(current_call);

        Ident t_var = next_t_var();
        emitLine(t_var + " := " + result);
        result = t_var;
        is_result_atomic = true;

        current_call--;

        labels = labels_backup;
        if (using_lazy_eval) {
            emitLine("if " + result + " then goto " + labels.label_true + " else goto " + labels.label_false);
        }
    }

    void visitListExpr(ListExpr *listExpr) override {
        for (auto i = listExpr->begin(); i != listExpr->end(); ++i) {
            if (current_call > 0) {
                Ident arg;

                boolLazyEvalChecker->is_lazy_eval = false;
                (*i)->accept(boolLazyEvalChecker);
                using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

                if (!using_lazy_eval) {
                    (*i)->accept(this);
                    if (is_result_atomic) {
                        arg = result;
                    } else {
                        arg = next_t_var();
                        emitLine(arg + " := " + result);
                    }
                } else {
                    arg = next_t_var();
                    lazyEval(arg, (*i));
                    using_lazy_eval = false;
                }

                call_to_args_string[current_call] += " " + arg;
                using_lazy_eval = false;
            }
        }
    }

    void varCommon(Ident var) {
        result = var;
        is_result_atomic = true;

        if (using_lazy_eval) {
            emitLine("if " + result + " then goto " + labels.label_true + " else goto " + labels.label_false);
        }
    }

    void visitEVar(EVar *expr) override {
        varCommon(expr->ident_);
    }

    void visitEBracketVar(EBracketVar *expr) override {
        varCommon(expr->ident_);
    }

//    void visitEComplex(EComplex *expr) override {} // todo teraz tylko CFunction więc jest git, potem rozwinąć

    void visitENullCast(ENullCast *expr) override {} // todo

    void visitELitInt(ELitInt *expr) override {
        result = std::to_string(expr->integer_);
        is_result_atomic = true;
    }

    void visitELitTrue(ELitTrue *expr) override {
        result = "1";
        is_result_atomic = true;
        if (using_lazy_eval) {
            emitLine("_goto " + labels.label_true);
        }
    }

    void visitELitFalse(ELitFalse *expr) override {
        result = "0";
        is_result_atomic = true;
        if (using_lazy_eval) {
            emitLine("_goto " + labels.label_false);
        }
    }

    void visitEString(EString *expr) override {
        result = "\"" + expr->string_ + "\"";
        is_result_atomic = true;
    }

    void visitNeg(Neg *expr) override {
        expr->expr_->accept(this);
        Ident t_var = next_t_var();
        emitLine(t_var + " := - " + result);
        result = t_var;
        is_result_atomic = true;
    }

    void visitNot(Not *expr) override {
        auto labels_backup = labels;
        auto t = labels.label_true;
        labels.label_true = labels.label_false;
        labels.label_false = t;

        expr->expr_->accept(this);
        Ident t_var = next_t_var();
        emitLine(t_var + " := ! " + result);
        result = t_var;
        is_result_atomic = true;

        labels = labels_backup;
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
        e_1 = expr->expr_1;
        e_2 = expr->expr_2;
        expr->relop_->accept(this);
        e_1 = nullptr;
        e_2 = nullptr;

        if (!using_lazy_eval || !expr->relop_->isEQUNE()) {
            visitBinOpp(expr->expr_1, expr->expr_2);
        }
    }

    void visitEOr(EOr *expr) override {
        auto labels_backup = labels;
        Ident label_middle = "_middle" + gen_next_cond_label();
        labels.label_false = label_middle;

        expr->expr_1->accept(this);
        emitRaw(label_middle + ":\n");
        labels = labels_backup;

        expr->expr_2->accept(this);
        labels = labels_backup;
    }

    void visitEAnd(EAnd *expr) override {
        auto labels_backup = labels;
        Ident label_middle = "_middle" + gen_next_cond_label();
        labels.label_true = label_middle;

        expr->expr_1->accept(this);
        emitRaw(label_middle + ":\n");
        labels = labels_backup;

        expr->expr_2->accept(this);
        labels = labels_backup;
    }

    void visitEQUNEcommon(Ident operator_) {
        if (using_lazy_eval) {
            Ident left;
            auto labels_backup = labels;
            boolLazyEvalChecker->is_lazy_eval = false;
            e_1->accept(boolLazyEvalChecker);
            using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;
            if (!using_lazy_eval) { // left side is simple eval
                e_1->accept(this);
                left = result;
                if (!is_result_atomic) {
                    Ident t_var = next_t_var();
                    emitLine(t_var + " := " + result);
                    left = t_var;
                }
            } else { // left side is lazy eval
                left = next_t_var();
                lazyEval(left, e_1);
            }

            labels = labels_backup;
            Ident right;
            boolLazyEvalChecker->is_lazy_eval = false;
            e_2->accept(boolLazyEvalChecker);
            using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;
            if (!using_lazy_eval) { // right side is simple eval
                e_2->accept(this);
                labels = labels_backup;
                right = result;
                if (!is_result_atomic) {
                    Ident t_var = next_t_var();
                    emitLine(t_var + " := " + result);
                    right = t_var;
                }
            } else { // right side is lazy eval
                right = next_t_var();
                lazyEval(right, e_2);
            }

            labels = labels_backup;
            using_lazy_eval = true;

            Ident t_var = next_t_var();
            emitLine(t_var + " := " + left + operator_ + right);
            result = t_var;
            is_result_atomic = true;
        }
    }

    void visitEQU(EQU *op) override {
        visitEQUNEcommon(" == ");
        if (using_lazy_eval) {
            emitLine("if " + result + " then goto " + labels.label_true + " else goto " + labels.label_false);
        }
    }

    void visitNE(NE *op) override {
        visitEQUNEcommon(" != ");

        if (using_lazy_eval) {
            emitLine("if " + result + " then goto " + labels.label_true + " else goto " + labels.label_false);
        }
    }

    void visitBinOpp(Expr *e1, Expr *e2) {
        auto labels_backup = labels;
        Ident operator_ = current_operator;
        e1->accept(this);
        labels = labels_backup;
        Ident left = result;
        if (!is_result_atomic) {
            Ident t_var = next_t_var();
            emitLine(t_var + " := " + result);
            left = t_var;
        }
        e2->accept(this);
        labels = labels_backup;
        Ident right = result;
        if (!is_result_atomic) {
            Ident t_var = next_t_var();
            emitLine(t_var + " := " + result);
            right = t_var;
        }

        Ident t_var = next_t_var();
        emitLine(t_var + " := " + left + operator_ + right);
        result = t_var;
        is_result_atomic = true;
        if (using_lazy_eval) {
            emitLine("if " + result + " then goto " + labels.label_true + " else goto " + labels.label_false);
        }
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

};