#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "Skeleton.C"
#include "LivenessVisitor.cpp"

class Dead_Code_Removal_Visitor : public Skeleton {
public:
    Program *program;
    int removed_lines = 0;
    bool remove_current_stmt = false;
    UIdent removing_ass_to;

    explicit Dead_Code_Removal_Visitor(Program *program) : program(program) {}

    void visitListNonJmpStmt(ListNonJmpStmt *listnonjmpstmt) override {
        for (ListNonJmpStmt::const_iterator i = listnonjmpstmt->begin(); i != listnonjmpstmt->end();) {
            remove_current_stmt = false;
            (*i)->accept(this);
            if (remove_current_stmt) {
                removed_lines++;
                std::cout << "REMOVING ASSIGNMENT TO " + removing_ass_to << std::endl;
                i = listnonjmpstmt->erase(i);
            } else {
                ++i;
            }
        }
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        if (stmt->out_vars.find(stmt->uident_) == stmt->out_vars.end()) {
            remove_current_stmt = true;
            removing_ass_to = stmt->uident_;
        }
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        if (stmt->atom_->var_name() == stmt->uident_) { // a := a, does nothing anyway
            remove_current_stmt = true;
            removing_ass_to = stmt->uident_;
        }

        if (stmt->out_vars.find(stmt->uident_) == stmt->out_vars.end()) {
            remove_current_stmt = true;
            removing_ass_to = stmt->uident_;
        }
    }
};

class Copy_Propagation_Visitor : public Skeleton {
public:
    std::vector<NonJmpStmt *>::iterator nonjmp_stmt_iterator;
    UIdent var_to_propagate;
    Atom *rhs;
    bool var_to_progate_reaches_further;

    bool changed;

    explicit Copy_Propagation_Visitor() {}

    void visitListNonJmpStmt(ListNonJmpStmt *listnonjmpstmt) override {
        nonjmp_stmt_iterator++; // start from the next stmt
        var_to_progate_reaches_further = true;

        for (ListNonJmpStmt::const_iterator i = nonjmp_stmt_iterator; i != listnonjmpstmt->end(); ++i) {
            (*i)->accept(this);
            if (!var_to_progate_reaches_further) {
                break;
            }
        }
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        if (stmt->atom_->var_name() == stmt->uident_) { // a := a, does nothing
            return;
        }
        if (stmt->uident_ == var_to_propagate) { // propagated var overwritten
            var_to_progate_reaches_further = false;
            return;
        }

        if (stmt->atom_->var_name() == var_to_propagate) { // propvar := 123, ...,  y := propvar  ->  y := 123
            changed = true;
            std::cout << "REPLACING noop " + var_to_propagate << std::endl;
            stmt->atom_ = rhs->clone();
        }
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        if (stmt->uident_ == var_to_propagate) { // propagated var overwritten
            var_to_progate_reaches_further = false;
            return;
        }

        if (stmt->atom_1->var_name() == var_to_propagate) { // propvar := 123, ...,  y := propvar + x  ->  y := 123 + x
            changed = true;
            std::cout << "REPLACING binop left " + var_to_propagate << std::endl;
            stmt->atom_1 = rhs->clone();
        }
        if (stmt->atom_2->var_name() == var_to_propagate) { // propvar := 123, ...,  y := x + propvar  ->  y := x + 123
            changed = true;
            std::cout << "REPLACING binop right " + var_to_propagate << std::endl;
            stmt->atom_2 = rhs->clone();
        }
    }

    void visitStmtCall(StmtCall *stmt) override {
        if (stmt->uident_1 == var_to_propagate) { // propagated var overwritten
            var_to_progate_reaches_further = false;
            return;
        }

        stmt->listatom_->accept(this);
    }

    void visitListAtom(ListAtom *list) override {
        for (int i = 0; i < list->size(); ++i) {
            if (list->at(i)->var_name() == var_to_propagate) {
                changed = true;
                std::cout << "REPLACING call arg " + var_to_propagate << std::endl;
                list->at(i) = rhs->clone();
            }
        }
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        if (stmt->atom_->var_name() == var_to_propagate) { // propvar := 1, ...,  if propvar  ->  if 1
            changed = true;
            std::cout << "REPLACING condjmp " + var_to_propagate << std::endl;
            stmt->atom_ = rhs->clone();
        }
    }

    void visitStmtRet(StmtRet *stmt) override {
        if (stmt->atom_->var_name() == var_to_propagate) { // propvar := 1, ...,  if propvar  ->  if 1
            changed = true;
            std::cout << "REPLACING ret " + var_to_propagate << std::endl;
            stmt->atom_ = rhs->clone();
        }
    }

};

class LCSE_Visitor : public Skeleton {
public:
    ListNonJmpStmt *block_list_nonjmp_stmt;
    JmpStmt *jmp_stmt;
    std::vector<NonJmpStmt *>::iterator nonjmp_stmt_iterator;

    bool changed;

    Copy_Propagation_Visitor *copyPropagationVisitor;

    explicit LCSE_Visitor() {
        copyPropagationVisitor = new Copy_Propagation_Visitor();
    }

    void reset() {
        changed = false;
        copyPropagationVisitor->changed = false;
    }

    void visitBlock(Block *block) override {
        jmp_stmt = block->listjmpstmt_->at(0);
        block_list_nonjmp_stmt = block->listnonjmpstmt_;

        block_list_nonjmp_stmt->accept(this);
        jmp_stmt->accept(this);

        if (copyPropagationVisitor->changed) {
            changed = true;
        }
    }

    void visitListNonJmpStmt(ListNonJmpStmt *listnonjmpstmt) override {
        for (auto i = listnonjmpstmt->begin(); i != listnonjmpstmt->end(); ++i) {
            nonjmp_stmt_iterator = i;
            (*i)->accept(this);
        }
    }

    void copy_propagate_variable(UIdent var_to_propagate, Atom *rhs) {
        copyPropagationVisitor->nonjmp_stmt_iterator = nonjmp_stmt_iterator;
        copyPropagationVisitor->var_to_propagate = var_to_propagate;
        copyPropagationVisitor->rhs = rhs;

        block_list_nonjmp_stmt->accept(copyPropagationVisitor);
        jmp_stmt->accept(copyPropagationVisitor);
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        auto rhs = stmt->atom_;
        copy_propagate_variable(stmt->uident_, rhs);
    }

    // TODO
//      void visitStmtBinOp(StmtBinOp *stmt) override {
//
//        }
};

class Optimization_Visitor : public Skeleton {
public:
    Program *program;
    Liveness_Visitor *livenessVisitor;
    Dead_Code_Removal_Visitor *deadCodeRemovalVisitor;
    LCSE_Visitor *lcseVisitor;

    std::map<UIdent, Block *> block_code;
    std::map <UIdent, std::set<UIdent >> succ;
    std::map <UIdent, std::set<UIdent >> pred;

    UIdent current_block;

    explicit Optimization_Visitor(Program *program, Liveness_Visitor *livenessVisitor) : program(program),
                                                                                         livenessVisitor(
                                                                                                 livenessVisitor) {
        deadCodeRemovalVisitor = new Dead_Code_Removal_Visitor(program);
        lcseVisitor = new LCSE_Visitor();
    }

    void optimize() {
        while (true) {
            deadCodeRemovalVisitor->removed_lines = 0;
            lcseVisitor->reset();
            // 1. remove dead code
            program->accept(deadCodeRemovalVisitor);

            // 2. LCSE + copy propagation
            program->accept(lcseVisitor);

            if (deadCodeRemovalVisitor->removed_lines == 0 && !lcseVisitor->changed) {
                break;
            }
            // 3. update liveness
            livenessVisitor->analyze_liveness_clear_init();
        }
    }

};