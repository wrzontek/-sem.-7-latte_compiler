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
    UIdent current_block;

    std::set <UIdent> next_stmt_in_vars;
    UIdent atom_var_name;
    StmtCall *current_call_stmt;

    void visitBlock(Block *block) override {
        current_block = block->uident_;
        next_stmt_in_vars = std::set<UIdent>();
        block->listjmpstmt_->accept(this);
        block->listnonjmpstmt_->accept(this);
    }

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        (*i)->accept(this); // we only use the first jump stmt
    }

    void visitListNonJmpStmt(ListNonJmpStmt *list_stmt) override {
        for (ListNonJmpStmt::reverse_iterator i = list_stmt->rbegin(); i != list_stmt->rend(); ++i) {
            (*i)->accept(this);
        }
    }

    void calc_in_vars(JmpStmt *stmt) {
        stmt->in_vars = stmt->out_vars;
        for (UIdent x: stmt->kill_vars) {
            stmt->in_vars.erase(x);
        }
        stmt->in_vars.insert(stmt->use_vars.begin(), stmt->use_vars.end());

        next_stmt_in_vars = stmt->in_vars;
    }

    void calc_in_vars(NonJmpStmt *stmt) {
        stmt->in_vars = stmt->out_vars;
        for (UIdent x: stmt->kill_vars) {
            stmt->in_vars.erase(x);
        }
        stmt->in_vars.insert(stmt->use_vars.begin(), stmt->use_vars.end());

        next_stmt_in_vars = stmt->in_vars;
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        atom_var_name = "";
        stmt->atom_->accept(this);
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtRet(StmtRet *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        atom_var_name = "";
        stmt->atom_->accept(this);
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtInc(StmtInc *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        stmt->use_vars.insert(stmt->uident_);
        calc_in_vars(stmt);
    }

    void visitStmtDecr(StmtDecr *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        stmt->use_vars.insert(stmt->uident_);
        calc_in_vars(stmt);
    }

    void visitAtomVar(AtomVar *var) override {
        atom_var_name = var->uident_;
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        stmt->kill_vars.insert(stmt->uident_);

        atom_var_name = "";
        stmt->atom_->accept(this);
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtNegOp(StmtNegOp *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        stmt->kill_vars.insert(stmt->uident_);

        atom_var_name = "";
        stmt->atom_->accept(this);
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        stmt->kill_vars.insert(stmt->uident_);

        atom_var_name = "";
        stmt->atom_1->accept(this);
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        atom_var_name = "";
        stmt->atom_2->accept(this);
        if (!atom_var_name.empty()) {
            stmt->use_vars.insert(atom_var_name);
        }

        calc_in_vars(stmt);
    }

    void visitListAtom(ListAtom *list_atom) override {
        for (ListAtom::iterator i = list_atom->begin(); i != list_atom->end(); ++i) {
            atom_var_name = "";
            (*i)->accept(this);
            if (!atom_var_name.empty()) {
                current_call_stmt->use_vars.insert(atom_var_name);
            }
        }
    }

    void visitStmtCall(StmtCall *stmt) override {
        stmt->out_vars = next_stmt_in_vars;

        stmt->kill_vars.insert(stmt->uident_1);

        current_call_stmt = stmt;
        stmt->listatom_->accept(this);
        current_call_stmt = nullptr;

        calc_in_vars(stmt);
    }


};

class Liveness_Visitor : public Skeleton {
public:
    Program *program;

    std::map <UIdent, std::set<UIdent >> &succ;
    std::map <UIdent, std::set<UIdent >> &pred;

    UIdent current_block;

    std::map <UIdent, std::set<UIdent >> block_out_vars;
    std::map <UIdent, std::set<UIdent >> block_in_vars;

    Statement_Liveness_Visitor *statementLivenessVisitor;
    Statement_Liveness_Printer *statementLivenessPrinter;

    explicit Liveness_Visitor(Program *program, std::map <UIdent, std::set<UIdent>> &succ,
                              std::map <UIdent, std::set<UIdent>> &pred) : program(program), succ(succ), pred(pred) {
        statementLivenessVisitor = new Statement_Liveness_Visitor();
        statementLivenessPrinter = new Statement_Liveness_Printer();
    }

    void analyze_liveness() {
        program->accept(statementLivenessVisitor);
        program->accept(statementLivenessPrinter);
    }


};