#pragma once

#include <string>
#include <set>
#include <vector>
#include "Skeleton.C"


class Constant_Calculator_Visitor : public Skeleton {
public:
    bool changed;
    NonJmpStmt *stmt_replacement;

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        (*i)->accept(this); // we only use the first jump stmt
    }

    void visitListNonJmpStmt(ListNonJmpStmt *listnonjmpstmt) override {
        stmt_replacement = nullptr;
        for (auto i = listnonjmpstmt->begin(); i != listnonjmpstmt->end(); ++i) {
            (*i)->accept(this);
            if (stmt_replacement != nullptr) {
//                std::cout << "calculated const expr\n";
                int index = std::distance(listnonjmpstmt->begin(), i);
                listnonjmpstmt->at(index) = stmt_replacement;
                stmt_replacement = nullptr;
                changed = true;
            }
        }
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        if (stmt->atom_1->is_int_constant() && stmt->atom_2->is_int_constant()) {
            int result;
            if (stmt->binop_->identifier() == "+") {
                result = stmt->atom_1->get_int_constant() + stmt->atom_2->get_int_constant();
            } else if (stmt->binop_->identifier() == "-") {
                result = stmt->atom_1->get_int_constant() - stmt->atom_2->get_int_constant();
            } else if (stmt->binop_->identifier() == "*") {
                result = stmt->atom_1->get_int_constant() * stmt->atom_2->get_int_constant();
            } else if (stmt->binop_->identifier() == "/") {
                result = stmt->atom_1->get_int_constant() / stmt->atom_2->get_int_constant();
            } else if (stmt->binop_->identifier() == "%") {
                result = stmt->atom_1->get_int_constant() % stmt->atom_2->get_int_constant();
            } else if (stmt->binop_->identifier() == "<") {
                result = stmt->atom_1->get_int_constant() < stmt->atom_2->get_int_constant() ? 1 : 0;
            } else if (stmt->binop_->identifier() == "<=") {
                result = stmt->atom_1->get_int_constant() <= stmt->atom_2->get_int_constant() ? 1 : 0;
            } else if (stmt->binop_->identifier() == ">") {
                result = stmt->atom_1->get_int_constant() > stmt->atom_2->get_int_constant() ? 1 : 0;
            } else if (stmt->binop_->identifier() == ">=") {
                result = stmt->atom_1->get_int_constant() >= stmt->atom_2->get_int_constant() ? 1 : 0;
            } else if (stmt->binop_->identifier() == "==") {
                result = stmt->atom_1->get_int_constant() == stmt->atom_2->get_int_constant() ? 1 : 0;
            } else if (stmt->binop_->identifier() == "!=") {
                result = stmt->atom_1->get_int_constant() != stmt->atom_2->get_int_constant() ? 1 : 0;
            }
            stmt_replacement = new StmtNoOp(stmt->uident_, new AtomInt(result));
            stmt_replacement->use_vars = stmt->use_vars;
            stmt_replacement->out_vars = stmt->out_vars;
            stmt_replacement->in_vars = stmt->in_vars;
            stmt_replacement->kill_vars = stmt->kill_vars;
            return;
        }

        if (stmt->atom_1->is_string_constant() && stmt->atom_2->is_string_constant()) {
            if (stmt->binop_->identifier() == "+") {
                std::string concat = stmt->atom_1->constant() + stmt->atom_2->constant();
                stmt_replacement = new StmtNoOp(stmt->uident_, new AtomStr(concat));
            } else if (stmt->binop_->identifier() == "==") {
                bool result = stmt->atom_1->constant() == stmt->atom_2->constant() ? 1 : 0;
                stmt_replacement = new StmtNoOp(stmt->uident_, new AtomInt(result));
            } else if (stmt->binop_->identifier() == "!=") {
                bool result = stmt->atom_1->constant() != stmt->atom_2->constant() ? 1 : 0;
                stmt_replacement = new StmtNoOp(stmt->uident_, new AtomInt(result));
            }
            stmt_replacement->use_vars = stmt->use_vars;
            stmt_replacement->out_vars = stmt->out_vars;
            stmt_replacement->in_vars = stmt->in_vars;
            stmt_replacement->kill_vars = stmt->kill_vars;
            return;
        }
    }


};
