#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "Printer.H"

std::vector<Expression *> intersection(std::vector<Expression *> a, std::vector<Expression *> b) {
    std::vector < Expression * > result;
    for (auto x: a) {
        for (auto y: b) {
            if (x == y) {
                result.push_back(x);
                break;
            }
        }
    }
    return result;
}

class Statement_GCSE_Visitor : public Skeleton {
public:
    std::vector<Expression *> current_const_exprs;
    UIdent this_stmt_lhs;
    UIdent this_stmt_rhs;

    bool replace_code = false;
    bool changed;

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        (*i)->accept(this); // we only use the first jump stmt
    }

    void visitListNonJmpStmt(ListNonJmpStmt *listnonjmpstmt) override {
        this_stmt_lhs = "";

        for (auto i = listnonjmpstmt->begin(); i != listnonjmpstmt->end(); ++i) {
            (*i)->accept(this);
            if (!this_stmt_lhs.empty()) {
                //std::cout << "REPLACING BINOP BOTH " + this_stmt_lhs + " with " + this_stmt_rhs << std::endl;
                int index = std::distance(listnonjmpstmt->begin(), i);
                auto replacement = new StmtNoOp(this_stmt_lhs, new AtomVar(this_stmt_rhs));
                listnonjmpstmt->at(index) = replacement;

                auto expr = new Expression(
                        replacement->uident_,
                        replacement->atom_,
                        nullptr,
                        nullptr
                );

                if (replacement->atom_->is_variable()) {
                    expr->used_vars.insert(replacement->atom_->var_name());
                }

                update_current_const_exprs(replacement->uident_, expr);

                this_stmt_lhs = "";
                this_stmt_rhs = "";
                changed = true;
            }
        }
    }

    void update_current_const_exprs(UIdent killed_var, Expression *new_expr) {
        for (auto i = current_const_exprs.begin(); i != current_const_exprs.end();) {
            auto expr = *i;
            if (expr->used_vars.find(killed_var) != expr->used_vars.end() || expr->assignment_to == killed_var) {
                i = current_const_exprs.erase(i);
            } else {
                ++i;
            }
        }
        if (new_expr != nullptr) {
            current_const_exprs.push_back(new_expr);
        }
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        if (stmt->uident_ == stmt->atom_->var_name()) {
            return;
        }

        if (replace_code) {
            for (auto &expr: current_const_exprs) {
                // copy propagation
                if (stmt->atom_->is_variable() && stmt->atom_->var_name() == expr->assignment_to && !expr->isBinOp()) {
                    //std::cout << "CHANGING NO-OP " + expr->assignment_to + " to " + expr->atom1->to_string() +  "\n";
                    changed = true;
                    stmt->atom_ = expr->atom1->clone();
                }
            }
        }

        auto expr = new Expression(
                stmt->uident_,
                stmt->atom_,
                nullptr,
                nullptr
        );
        if (stmt->atom_->is_variable()) {
            expr->used_vars = {stmt->atom_->var_name()};
        }

        update_current_const_exprs(stmt->uident_, expr);
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        if (replace_code) {
            for (auto &expr: current_const_exprs) {
                // copy propagation
                if (!expr->isBinOp()) {
                    if (stmt->atom_1->is_variable() && stmt->atom_1->var_name() == expr->assignment_to) {
                        changed = true;
                        //std::cout << "CHANGING BINOP LEFT " + expr->assignment_to + " to " + expr->atom1->to_string() +  "\n";
                        stmt->atom_1 = expr->atom1->clone();
                    }

                    if (stmt->atom_2->is_variable() && stmt->atom_2->var_name() == expr->assignment_to) {
                        changed = true;
                        //std::cout << "CHANGING BINOP RIGHT " + expr->assignment_to + " to " + expr->atom1->to_string() + "\n";
                        stmt->atom_2 = expr->atom1->clone();
                    }
                }

                // CSE
                if (expr->isBinOp()) {
                    auto this_expr = new Expression(
                            "",
                            stmt->atom_1,
                            stmt->atom_2,
                            stmt->binop_
                    );

                    if (this_expr->sameExpression(expr)) {
                        this_stmt_rhs = expr->assignment_to;
                        this_stmt_lhs = stmt->uident_;
                        //std::cout << "CHANGING LCSE RHS: " + this_stmt_rhs + " LHS: " + this_stmt_lhs + "\n";
                    }
                }
            }
        }
        if (!this_stmt_lhs.empty()) { // robimy to w visitListNonJmpStmt
            auto expr = new Expression(
                    stmt->uident_,
                    stmt->atom_1,
                    stmt->atom_2,
                    stmt->binop_
            );
            if (stmt->atom_1->is_variable()) {
                expr->used_vars.insert(stmt->atom_1->var_name());
            }
            if (stmt->atom_2->is_variable()) {
                expr->used_vars.insert(stmt->atom_2->var_name());
            }
            update_current_const_exprs(stmt->uident_, expr);
        }
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        if (replace_code) {
            for (auto &expr: current_const_exprs) {
                if (!expr->isBinOp() && stmt->atom_->is_variable() && stmt->atom_->var_name() == expr->assignment_to) {
                    changed = true;
                    //std::cout << "CHANGING CONDJUMP " + expr->assignment_to + " to " + expr->atom1->to_string() +  "\n";
                    stmt->atom_ = expr->atom1->clone();
                }
            }
        }
    }

    void visitStmtRet(StmtRet *stmt) override {
        if (replace_code) {
            for (auto &expr: current_const_exprs) {
                if (!expr->isBinOp() && stmt->atom_->is_variable() && stmt->atom_->var_name() == expr->assignment_to) {
                    changed = true;
                    //std::cout << "CHANGING RET " + expr->assignment_to + " to " + expr->atom1->to_string() +  "\n";
                    stmt->atom_ = expr->atom1->clone();
                }
            }
        }
    }

    void visitListAtom(ListAtom *list) override {
        if (replace_code) {
            for (int i = 0; i < list->size(); ++i) {
                for (auto &expr: current_const_exprs) {
                    if (list->at(i)->is_variable() && list->at(i)->var_name() == expr->assignment_to &&
                        !expr->isBinOp()) {
                        //std::cout << "CHANGING CALL ARG " + expr->assignment_to + " to " + expr->atom1->to_string() +  "\n";
                        changed = true;
                        list->at(i) = expr->atom1->clone();
                    }
                }
            }
        }
    }

    void visitStmtCall(StmtCall *stmt) override {
        stmt->listatom_->accept(this);

        update_current_const_exprs(stmt->uident_1, nullptr);
    }

};
