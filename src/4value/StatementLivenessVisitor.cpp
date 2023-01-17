#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "Printer.H"

class Statement_Liveness_Printer : public Skeleton {
public:
    UIdent atom_var_name;

    void visitBlock(Block *block) override {
        std::cout << "BLOCK: " + block->uident_ << std::endl;
        block->listnonjmpstmt_->accept(this);
        block->listjmpstmt_->accept(this);
    }

    void printSet(const std::set <UIdent> &set) {
        std::cout << "{";
        for (auto it = set.begin(); it != set.end(); ++it) {
            if (it != set.begin()) {
                std::cout << ", ";
            }
            std::cout << *it;
        }
        std::cout << "}" << std::endl;
    }

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        auto stmt = (*i);

        PrintAbsyn *p = new PrintAbsyn();
        printf("%s\n", p->print(stmt));

        std::cout << "out: ";
        printSet(stmt->out_vars);
        std::cout << "kill: ";
        printSet(stmt->kill_vars);
        std::cout << "use: ";
        printSet(stmt->use_vars);
        std::cout << "in: ";
        printSet(stmt->in_vars);
        std::cout << "\n";
    }

    void visitListNonJmpStmt(ListNonJmpStmt *list_stmt) override {
        for (ListNonJmpStmt::const_iterator i = list_stmt->begin(); i != list_stmt->end(); ++i) {
            auto stmt = (*i);

            PrintAbsyn *p = new PrintAbsyn();
            printf("%s\n", p->print(stmt));
            std::cout << "out: ";
            printSet(stmt->out_vars);
            std::cout << "kill: ";
            printSet(stmt->kill_vars);
            std::cout << "use: ";
            printSet(stmt->use_vars);
            std::cout << "in: ";
            printSet(stmt->in_vars);
            std::cout << "\n";

        }
    }

};

class Statement_Liveness_Visitor : public Skeleton {
public:
    std::set <UIdent> current_stmt_out_vars;
    StmtCall *current_call_stmt;
    std::set <UIdent> block_in_vars;

    void visitBlock(Block *block) override {
//        current_stmt_out_vars = std::set<UIdent>();
        block->listjmpstmt_->accept(this);
        if (!block->listnonjmpstmt_->empty()) block->listnonjmpstmt_->accept(this);
    }

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        (*i)->accept(this); // we only use the first jump stmt
        block_in_vars = (*(list_jmp_stmt->begin()))->in_vars;
    }

    void visitListNonJmpStmt(ListNonJmpStmt *list_stmt) override {
        for (ListNonJmpStmt::reverse_iterator i = list_stmt->rbegin(); i != list_stmt->rend(); ++i) {
            (*i)->accept(this);
        }
        block_in_vars = (*(list_stmt->begin()))->in_vars;
    }

    void calc_in_vars(JmpStmt *stmt) {
        stmt->in_vars = stmt->out_vars;
        for (UIdent x: stmt->kill_vars) {
            stmt->in_vars.erase(x);
        }
        stmt->in_vars.insert(stmt->use_vars.begin(), stmt->use_vars.end());

        current_stmt_out_vars = stmt->in_vars;
    }

    void calc_in_vars(NonJmpStmt *stmt) {
        stmt->in_vars = stmt->out_vars;
        for (UIdent x: stmt->kill_vars) {
            stmt->in_vars.erase(x);
        }
        stmt->in_vars.insert(stmt->use_vars.begin(), stmt->use_vars.end());

        current_stmt_out_vars = stmt->in_vars;
    }

    void visitStmtGoNext(StmtGoNext *stmt) override {
        stmt->out_vars = current_stmt_out_vars;
        calc_in_vars(stmt);
    }

    void visitStmtGoto(StmtGoto *stmt) override {
        stmt->out_vars = current_stmt_out_vars;
        calc_in_vars(stmt);
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        auto atom_var_name = stmt->atom_->var_name();
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtRet(StmtRet *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        auto atom_var_name = stmt->atom_->var_name();
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtVRet(StmtVRet *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        calc_in_vars(stmt);
    }

    void visitStmtDoNothing(StmtDoNothing *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        calc_in_vars(stmt);
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        stmt->kill_vars.insert(stmt->uident_);

        auto atom_var_name = stmt->atom_->var_name();
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        stmt->kill_vars.insert(stmt->uident_);

        auto atom_var_name = stmt->atom_1->var_name();
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        atom_var_name = stmt->atom_2->var_name();
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitListAtom(ListAtom *list_atom) override {
        for (ListAtom::iterator i = list_atom->begin(); i != list_atom->end(); ++i) {
            auto atom_var_name = (*i)->var_name();
            if (!atom_var_name.empty()) {
                current_call_stmt->use_vars.insert(atom_var_name);
            }
        }
    }

    void visitStmtCall(StmtCall *stmt) override {
        stmt->out_vars = current_stmt_out_vars;

        stmt->kill_vars.insert(stmt->uident_1);

        current_call_stmt = stmt;
        stmt->listatom_->accept(this);
        current_call_stmt = nullptr;

        calc_in_vars(stmt);
    }


};
