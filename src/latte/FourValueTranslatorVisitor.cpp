#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include <algorithm>
#include "Absyn.H"
#include "Skeleton.C"
#include "Common.cpp"
#include "TypeVisitor.cpp"

class BoolLazyEvalChecker : public Skeleton {
public:
    bool is_lazy_eval = false;
    bool has_call = false;

    explicit BoolLazyEvalChecker() {}

    void visitEAnd(EAnd *e) override {
        is_lazy_eval = true;
    }

    void visitEOr(EOr *e) override {
        is_lazy_eval = true;
    }

    void visitCFunction(CFunction *e) override {
        has_call = true;
    } // do not consider function arguments for lazy eval, they are handled separately

//    void visitMethod(Method *e) override {
//        has_call = true;
//    } // do not consider method arguments for lazy eval, TODO they are  handled separately
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

    bool current_function_is_void;

    bool is_last_stmt = false;
    bool inside_block = false;

    bool block_emit_labels_and_gotos = true;

    bool using_lazy_eval = false;
    bool negating = false;
    labels_struct labels;

    int current_call = 0;
    int current_depth = 0;
    std::map <Ident, std::vector<int>> ident_to_declarations;

    std::map<int, Ident> call_to_args_string;
    std::map <Ident, Ident> current_function_arg_order;
    std::set <Ident> current_function_arg_strings;

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
        ident_to_declarations = std::map < Ident, std::vector < int >> ();
        current_function_arg_order.clear();
        current_function_arg_strings.clear();
        using_lazy_eval = false;
        current_depth = 0;
        current_function_is_void = (typeVisitor->getType(fnDef->type_)->name == "void");

        emitRaw(fnDef->ident_ + ":\n");
        fnDef->listarg_->accept(this);
        fnDef->block_->accept(this);

        if (typeVisitor->getType(fnDef->type_)->name == "void") {
            emitLine("return;"); // can be overkill, but better 2 returns than none
        }

        emitRaw("\n");
    }

    void visitListArg(ListArg *listArg) override {
        int arg_num = 0;
        for (auto arg = listArg->begin(); arg != listArg->end(); ++arg) {
            current_function_arg_order[(*arg)->ident()] = std::to_string(arg_num);
            if ((*arg)->is_string()) {
                current_function_arg_strings.insert((*arg)->ident());
            }
            arg_num++;
        }
    }

    void visitListStmt(ListStmt *list_stmt) override {
        for (ListStmt::iterator stmt = list_stmt->begin(); stmt != list_stmt->end(); ++stmt) {
            auto copy = stmt;
            if (!inside_block) { // so inner block bodies don't count
                is_last_stmt = (++copy) == list_stmt->end();
            }

            (*stmt)->accept(this);
        }
    }

    void visitDecl(Decl *stmt) override {
        using_lazy_eval = false;
        current_decl_type = typeVisitor->getType(stmt->type_)->name;
        stmt->listitem_->accept(this);
    }

    void add_to_declaration_map(Ident var_name_raw) {
        std::vector<int> declarations = std::vector<int>();
        if (ident_to_declarations.find(var_name_raw) != ident_to_declarations.end()) {
            declarations = ident_to_declarations[var_name_raw];
        }
        declarations.push_back(current_depth);
        ident_to_declarations[var_name_raw] = declarations;
    }

    void visitNoInit(NoInit *stmt) override {
        using_lazy_eval = false;
        auto var_name = "_d" + std::to_string(current_depth) + "_" + stmt->ident_;
        add_to_declaration_map(stmt->ident_);

        if (current_decl_type == "string") {
            emitLine(var_name + " := \"\"");
        } else {
            emitLine(var_name + " := 0");
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
        emitLine("_go_next " + labels.label_end);

        emitRaw(labels.label_end + ":\n");

        labels = labels_backup;
    }

    void visitInit(Init *stmt) override {
        boolLazyEvalChecker->is_lazy_eval = false;
        stmt->expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        auto var_name = "_d" + std::to_string(current_depth) + "_" + stmt->ident_;
        add_to_declaration_map(stmt->ident_);

        if (!using_lazy_eval) {
            stmt->expr_->accept(this);
            emitLine(var_name + " := " + result);
        } else {
            lazyEval(var_name, stmt->expr_);
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
        boolLazyEvalChecker->has_call = false;
        stmt->expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (boolLazyEvalChecker->has_call) { // if not function/method do nothing
            if (!using_lazy_eval) {
                stmt->expr_->accept(this);
            } else {
                lazyEval("", stmt->expr_);
                using_lazy_eval = false;
            }
        }
    }

    void visitIncr(Incr *stmt) override {
        using_lazy_eval = false;
        stmt->expr_->accept(this);
        if (is_result_atomic) {
            emitLine(result + " := " + result + " + 1");
        } else {
            auto t_var = next_t_var();
            emitLine(t_var + " := " + result);
            emitLine(t_var + " := " + t_var + " + 1");
            result = t_var;
        }
        is_result_atomic = true;
    }

    void visitDecr(Decr *stmt) override {
        using_lazy_eval = false;
        stmt->expr_->accept(this);

        if (is_result_atomic) {
            emitLine(result + " := " + result + " - 1");
        } else {
            auto t_var = next_t_var();
            emitLine(t_var + " := " + result);
            emitLine(t_var + " := " + t_var + " - 1");
            result = t_var;
        }
        is_result_atomic = true;
    }

    void visitRet(Ret *stmt) override {
        boolLazyEvalChecker->is_lazy_eval = false;
        boolLazyEvalChecker->has_call = false;
        stmt->expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (!using_lazy_eval) {
            stmt->expr_->accept(this);
        } else {
            lazyEval("_res", stmt->expr_);
            result = "_res";
            using_lazy_eval = false;
        }
        emitLine("return " + result);
    }

    void visitVRet(VRet *stmt) override {
        using_lazy_eval = false;
        emitLine("return;");
    }

    void clear_deeper_declarations() {
        for (auto &pair: ident_to_declarations) {
            auto &depths = pair.second;
            depths.erase(std::remove_if(depths.begin(), depths.end(),
                                        [this](int value) { return value > this->current_depth; }),
                         depths.end());
        }
    }

    void visitBStmt(BStmt *stmt) override {
        if (!stmt->block_->isEmpty()) { // do nothing for empty block
            bool inside_block_backup = inside_block;
            inside_block = true;
            bool emit_labels_gotos_backup = block_emit_labels_and_gotos;
            using_lazy_eval = false;
            Ident t_block, after_t_block;
            if (block_emit_labels_and_gotos) {
                t_block = next_t_block();
                after_t_block = "_after" + t_block;
                emitLine("_go_next " + t_block);
                emitRaw(t_block + ":\n");
            }

            block_emit_labels_and_gotos = true;
            current_depth++;
            stmt->block_->accept(this);
            current_depth--;
            block_emit_labels_and_gotos = emit_labels_gotos_backup;

            clear_deeper_declarations();

            if (block_emit_labels_and_gotos && !is_last_stmt) {
                emitLine("_go_next " + after_t_block);
                emitRaw(after_t_block + ":\n");
            }

            inside_block = inside_block_backup;
        }
    }

    Ident getCondAtom(Expr *expr_) {
        Ident cond_atom;
        boolLazyEvalChecker->is_lazy_eval = false;
        expr_->accept(boolLazyEvalChecker);
        using_lazy_eval = boolLazyEvalChecker->is_lazy_eval;

        if (!using_lazy_eval) {
            expr_->accept(this);
            if (is_result_atomic) {
                cond_atom = result;
            } else {
                cond_atom = next_t_var();
                emitLine(cond_atom + " := " + result);
            }
        } else {
            cond_atom = next_t_var();
            lazyEval(cond_atom, expr_);
            using_lazy_eval = false;
        }
        return cond_atom;
    }

    void visitCond(Cond *stmt) override {
        next_t_block_number++;
        auto if_true = "_if_true_" + std::to_string(next_t_block_number);
        auto end_if = "_end_if_" + std::to_string(next_t_block_number);
        if (!stmt->expr_->isAlwaysTrue() && (current_function_is_void || !is_last_stmt)) {
            auto cond_atom = getCondAtom(stmt->expr_);
            emitLine("if " + cond_atom + " then _goto " + if_true + " else _goto " + end_if);
        } else {
            emitLine("_goto " + if_true); // typeChecker guarantees correctness
        }

        emitRaw(if_true + ":\n");
        block_emit_labels_and_gotos = false;
        stmt->stmt_->accept(this);
        block_emit_labels_and_gotos = true;

        if (!is_last_stmt) {
            emitLine("_go_next " + end_if);
            emitRaw(end_if + ":\n");
        }
    }

    void visitCondElse(CondElse *stmt) override {
        auto cond_atom = getCondAtom(stmt->expr_);

        next_t_block_number++;
        auto if_true = "_if_true_" + std::to_string(next_t_block_number);
        auto if_false = "_if_false_" + std::to_string(next_t_block_number);
        auto end_if = "_end_if_" + std::to_string(next_t_block_number);

        if (!stmt->expr_->isAlwaysTrue() && !stmt->expr_->isAlwaysFalse()) {
            emitLine("if " + cond_atom + " then _goto " + if_true + " else _goto " + if_false);
            emitRaw(if_true + ":\n");

            block_emit_labels_and_gotos = false;
            stmt->stmt_1->accept(this);
            block_emit_labels_and_gotos = true;

            if (!is_last_stmt) {
                emitLine("_goto " + end_if);
            } else {
                emitLine("return;");
            }

            emitRaw(if_false + ":\n");

            block_emit_labels_and_gotos = false;
            stmt->stmt_2->accept(this);
            block_emit_labels_and_gotos = true;

            if (!is_last_stmt) {
                emitLine("_go_next " + end_if);
                emitRaw(end_if + ":\n");
            } else {
                emitLine("return;");
            }
        } else if (stmt->expr_->isAlwaysTrue()) {
            emitLine("_goto " + if_true); // typeChecker guarantees correctness
            emitRaw(if_true + ":\n");
            block_emit_labels_and_gotos = false;
            stmt->stmt_1->accept(this);
            block_emit_labels_and_gotos = true;
            if (!is_last_stmt) {
                emitLine("_go_next " + end_if);
                emitRaw(end_if + ":\n");
            } else {
                emitLine("return;");
            }
        } else if (stmt->expr_->isAlwaysFalse()) {
            emitLine("_goto " + if_false); // typeChecker guarantees correctness
            emitRaw(if_false + ":\n");
            block_emit_labels_and_gotos = false;
            stmt->stmt_2->accept(this);
            block_emit_labels_and_gotos = true;
            if (!is_last_stmt) {
                emitLine("_go_next " + end_if);
                emitRaw(end_if + ":\n");
            } else {
                emitLine("return;");
            }
        }
    }

    void visitWhile(While *stmt) override {
        next_t_block_number++;
        auto while_cond = "_while_cond_" + std::to_string(next_t_block_number);
        auto while_body = "_while_body_" + std::to_string(next_t_block_number);
        auto end_while = "_end_while_" + std::to_string(next_t_block_number);

        if (!is_last_stmt) {
            emitLine("_goto " + while_cond);
        } else {
            emitLine("_go_next " + while_body);
        }

        emitRaw(while_body + ":\n");
        block_emit_labels_and_gotos = false;
        stmt->stmt_->accept(this);
        block_emit_labels_and_gotos = true;

        if (!is_last_stmt) {
            emitLine("_go_next " + while_cond);
            emitRaw(while_cond + ":\n");
            auto cond_atom = getCondAtom(stmt->expr_);
            emitLine("if " + cond_atom + " then _goto " + while_body + " else _goto " + end_while);

            emitRaw(end_while + ":\n");
        }
    }

//    void visitForEach(ForEach *stmt) override {
//        using_lazy_eval = false;
//
//    } // todo

///////////////////////////////////////////////////////////////////////////////////////////////////////////

    void visitCFunction(CFunction *expr) override {
        auto using_lazy_eval_backup = using_lazy_eval;
        auto labels_backup = labels;
        current_call++;
        expr->listexpr_->accept(this);

        result = "_call " + expr->ident_ + call_to_args_string[current_call] + " ;";
        call_to_args_string.erase(current_call);

        Ident t_var = next_t_var();
        emitLine(t_var + " := " + result);
        result = t_var;
        is_result_atomic = true;

        current_call--;

        labels = labels_backup;
        using_lazy_eval = using_lazy_eval_backup;
        if (using_lazy_eval) {
            emitLine("if " + result + " then _goto " + labels.label_true + " else _goto " + labels.label_false);
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
        if (ident_to_declarations.find(var) == ident_to_declarations.end()) {
            // declaration not found - can only happen if var is function argument
            if (current_function_arg_strings.find(var) != current_function_arg_strings.end()) {
                result = "__str__" + current_function_arg_order[var];
            } else {
                result = "__arg__" + current_function_arg_order[var];
            }
            // for (auto arg : current_function_arg
        } else {
            auto declarations = ident_to_declarations[var];
            int declaration_depth = declarations[declarations.size() - 1];
            result = "_d" + std::to_string(declaration_depth) + "_" + var;
        }
        is_result_atomic = true;

        if (using_lazy_eval) {
            if (negating) {
                Ident t_var = next_t_var();
                emitLine(t_var + " := - " + result);
                result = t_var;
            }
            emitLine("if " + result + " then _goto " + labels.label_true + " else _goto " + labels.label_false);
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
        result = expr->string_;
        std::string new_str;
        for (auto ch: result) {
            switch (ch) {
                case '\'':
                    new_str += "\\'";
                    break;
                case '\"':
                    new_str += "\\\"";
                    break;
                case '\?':
                    new_str += "\\?";
                    break;
                case '\\':
                    new_str += "\\\\";
                    break;
                case '\a':
                    new_str += "\\a";
                    break;
                case '\b':
                    new_str += "\\b";
                    break;
                case '\f':
                    new_str += "\\f";
                    break;
                case '\n':
                    new_str += "\\n";
                    break;
                case '\r':
                    new_str += "\\r";
                    break;
                case '\t':
                    new_str += "\\t";
                    break;
                case '\v':
                    new_str += "\\v";
                    break;
                default:
                    new_str += ch;
            }
        }
        result = "\"" + new_str + "\"";
        is_result_atomic = true;
    }

    void visitNeg(Neg *expr) override {
        expr->expr_->accept(this);
        Ident t_var = next_t_var();
        emitLine(t_var + " :=  0 - " + result);
        result = t_var;
        is_result_atomic = true;
    }

    void visitNot(Not *expr) override {
        auto labels_backup = labels;
        auto t = labels.label_true;
        labels.label_true = labels.label_false;
        labels.label_false = t;

        negating = true;
        expr->expr_->accept(this);
        negating = false;
        Ident t_var = next_t_var();
        if (!using_lazy_eval) {
            emitLine(t_var + " := 1 - " + result);
            result = t_var;
            is_result_atomic = true;
        }

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

    void visitEQUNEcommon() {
        if (using_lazy_eval) {
            Ident operator_ = current_operator;

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

//            if (typeVisitor->getType(e1)->name == "string") {
//                if (operator_ == " == ")
//                    operator_ = "  _==_ "; // TODO
//                else if (operator_ == " != ")
//                    operator_ = " _!=! "; // TODO
//            }

            Ident t_var = next_t_var();
            emitLine(t_var + " := " + left + operator_ + right);
            result = t_var;
            is_result_atomic = true;
            emitLine("if " + result + " then _goto " + labels.label_true + " else _goto " + labels.label_false);
        }
    }

    void visitEQU(EQU *op) override {
        current_operator = " == ";
        visitEQUNEcommon();
    }

    void visitNE(NE *op) override {
        current_operator = " != ";
        visitEQUNEcommon();
    }

    void visitBinOpp(Expr *e1, Expr *e2) {
        auto labels_backup = labels;
        auto using_lazy_eval_backup = using_lazy_eval;
        using_lazy_eval = false;
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
//        if (operator_ == " + " && typeVisitor->getType(e1)->name == "string") {
//            operator_ = "  _+_ "; // TODO
//        }
        emitLine(t_var + " := " + left + operator_ + right);
        result = t_var;
        is_result_atomic = true;

        using_lazy_eval = using_lazy_eval_backup;
        if (using_lazy_eval) {
            emitLine("if " + result + " then _goto " + labels.label_true + " else _goto " + labels.label_false);
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