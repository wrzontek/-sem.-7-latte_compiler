#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "Skeleton.C"
#include "LivenessVisitor.cpp"
#include "GCSEVisitor.cpp"
#include "ConstantCalculatorVisitor.cpp"

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
                //std::cout << "REMOVING ASSIGNMENT TO " + removing_ass_to << std::endl;
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
            //std::cout << "REPLACING noop " + var_to_propagate << std::endl;
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
            //std::cout << "REPLACING binop left " + var_to_propagate << std::endl;
            stmt->atom_1 = rhs->clone();
        }
        if (stmt->atom_2->var_name() == var_to_propagate) { // propvar := 123, ...,  y := x + propvar  ->  y := x + 123
            changed = true;
            //std::cout << "REPLACING binop right " + var_to_propagate << std::endl;
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
                //std::cout << "REPLACING call arg " + var_to_propagate << std::endl;
                list->at(i) = rhs->clone();
            }
        }
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        if (stmt->atom_->var_name() == var_to_propagate) { // propvar := 1, ...,  if propvar  ->  if 1
            changed = true;
            //std::cout << "REPLACING condjmp " + var_to_propagate << std::endl;
            stmt->atom_ = rhs->clone();
        }
    }

    void visitStmtRet(StmtRet *stmt) override {
        if (stmt->atom_->var_name() == var_to_propagate) { // propvar := 1, ...,  if propvar  ->  if 1
            changed = true;
            //std::cout << "REPLACING ret " + var_to_propagate << std::endl;
            stmt->atom_ = rhs->clone();
        }
    }

};

class Expression_Propagation_Visitor : public Skeleton {
public:
    std::vector<NonJmpStmt *>::iterator nonjmp_stmt_iterator;

    BinOp *propagated_expression_binop;
    Atom *rhs_atom_1;
    Atom *rhs_atom_2;

    UIdent result_var;
    bool expression_to_progate_reaches_further;
    UIdent this_stmt_lhs;

    bool changed;

    explicit Expression_Propagation_Visitor() {}

    void visitListNonJmpStmt(ListNonJmpStmt *listnonjmpstmt) override {
        nonjmp_stmt_iterator++; // start from the next stmt
        expression_to_progate_reaches_further = true;
        this_stmt_lhs = "";

        for (auto i = nonjmp_stmt_iterator; i != listnonjmpstmt->end(); ++i) {
            (*i)->accept(this);
            if (!this_stmt_lhs.empty()) {
                //std::cout << "REPLACING BINOP BOTH " + this_stmt_lhs + " with " + result_var << std::endl;
                int index = std::distance(listnonjmpstmt->begin(), i);
                listnonjmpstmt->at(index) = new StmtNoOp(this_stmt_lhs, new AtomVar(result_var));
                this_stmt_lhs = "";
            }
            if (!expression_to_progate_reaches_further) {
                break;
            }
        }
    }

    bool atomsEqual(Atom *atom1, Atom *atom2) {
        if (atom1->is_int_constant() && atom2->is_int_constant()) {
            return atom1->get_int_constant() == atom2->get_int_constant();
        }
        if (atom1->is_string_constant() && atom2->is_string_constant()) {
            return atom1->constant() == atom2->constant();
        }
        if (!atom1->var_name().empty() && !atom2->var_name().empty()) {
            return atom1->var_name() == atom2->var_name();
        }

        return false;
    }

    bool expressionIsPropagatedExpression(BinOp *binop, Atom *atom1, Atom *atom2) {
        return binop->identifier() == propagated_expression_binop->identifier() &&
               ((atomsEqual(atom1, rhs_atom_1) && atomsEqual(atom2, rhs_atom_2)) ||
                (binop->order_agnostic() && atomsEqual(atom2, rhs_atom_1) && atomsEqual(atom1, rhs_atom_2)));
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        if (stmt->atom_->var_name() == stmt->uident_) { // a := a, does nothing
            return;
        }
        if (stmt->uident_ == rhs_atom_1->var_name() ||
            stmt->uident_ == rhs_atom_2->var_name()) { // part of propagated expression overwritten
            expression_to_progate_reaches_further = false;
            return;
        }
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        if (stmt->uident_ == rhs_atom_1->var_name() ||
            stmt->uident_ == rhs_atom_2->var_name()) { // part of propagated expression overwritten
            expression_to_progate_reaches_further = false;
            return;
        }

        if (expressionIsPropagatedExpression(stmt->binop_, stmt->atom_1, stmt->atom_2)) {
            changed = true;
            this_stmt_lhs = stmt->uident_;
        }
    }

    void visitStmtCall(StmtCall *stmt) override {
        if (stmt->uident_1 == rhs_atom_1->var_name() ||
            stmt->uident_1 == rhs_atom_2->var_name()) { // part of propagated expression overwritten
            expression_to_progate_reaches_further = false;
            return;
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
    Expression_Propagation_Visitor *expressionPropagationVisitor;

    explicit LCSE_Visitor() {
        copyPropagationVisitor = new Copy_Propagation_Visitor();
        expressionPropagationVisitor = new Expression_Propagation_Visitor();
    }

    void reset() {
        changed = false;
        copyPropagationVisitor->changed = false;
        expressionPropagationVisitor->changed = false;
    }

    void visitBlock(Block *block) override {
        jmp_stmt = block->listjmpstmt_->at(0);
        block_list_nonjmp_stmt = block->listnonjmpstmt_;

        block_list_nonjmp_stmt->accept(this);
        jmp_stmt->accept(this);

        if (copyPropagationVisitor->changed || expressionPropagationVisitor->changed) {
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

    void propagate_expression(UIdent result_var, BinOp *binOp, Atom *rhs_atom_1, Atom *rhs_atom_2) {
        expressionPropagationVisitor->nonjmp_stmt_iterator = nonjmp_stmt_iterator;
        expressionPropagationVisitor->result_var = result_var;
        expressionPropagationVisitor->rhs_atom_1 = rhs_atom_1;
        expressionPropagationVisitor->rhs_atom_2 = rhs_atom_2;
        expressionPropagationVisitor->propagated_expression_binop = binOp;

        block_list_nonjmp_stmt->accept(expressionPropagationVisitor);
        jmp_stmt->accept(expressionPropagationVisitor);
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        copy_propagate_variable(stmt->uident_, stmt->atom_);
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        propagate_expression(stmt->uident_, stmt->binop_, stmt->atom_1, stmt->atom_2);
    }
};

class Optimization_Visitor : public Skeleton {
public:
    bool lcse_only = false;
    Program *program;
    Liveness_Visitor *livenessVisitor;
    Dead_Code_Removal_Visitor *deadCodeRemovalVisitor;
    Constant_Calculator_Visitor *constantCalculatorVisitor;
    LCSE_Visitor *lcseVisitor;
    GCSE_Visitor *gcseVisitor;

    std::map<UIdent, Block *> &block_code;
    std::map <UIdent, std::set<UIdent >> &succ;
    std::map <UIdent, std::set<UIdent >> &pred;

    UIdent current_block;

    explicit Optimization_Visitor(Program *program, Liveness_Visitor *livenessVisitor,
                                  std::map <UIdent, std::set<UIdent >> &succ,
                                  std::map <UIdent, std::set<UIdent >> &pred,
                                  std::map<UIdent, Block *> &block_code) : program(program),
                                                                           livenessVisitor(livenessVisitor), succ(succ),
                                                                           pred(pred), block_code(block_code) {
        deadCodeRemovalVisitor = new Dead_Code_Removal_Visitor(program);
        lcseVisitor = new LCSE_Visitor();
        constantCalculatorVisitor = new Constant_Calculator_Visitor();
        gcseVisitor = new GCSE_Visitor(program, succ, pred, block_code);
    }

    void optimize() {
        while (true) {
            deadCodeRemovalVisitor->removed_lines = 0;
            lcseVisitor->reset();
            gcseVisitor->reset();
            constantCalculatorVisitor->changed = false;

            // 0. calculate constant expressions
            program->accept(constantCalculatorVisitor);

            // 1. remove dead code
            program->accept(deadCodeRemovalVisitor);

            // 2. LCSE + copy propagation
            if (lcse_only) {
                program->accept(lcseVisitor);
            } else {
                gcseVisitor->run_gcse();
            }

            if (deadCodeRemovalVisitor->removed_lines == 0 && !gcseVisitor->changed && !lcseVisitor->changed &&
                !constantCalculatorVisitor->changed) {
                break;
            }
            // 3. update liveness
            livenessVisitor->analyze_liveness_clear_init();
        }
    }

};