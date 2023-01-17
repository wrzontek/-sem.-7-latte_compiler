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
        if (stmt->out_vars.find(stmt->uident_) == stmt->out_vars.end()) {
            remove_current_stmt = true;
            removing_ass_to = stmt->uident_;
        }
    }
};

class Optimization_Visitor : public Skeleton {
public:
    Program *program;
    Liveness_Visitor *livenessVisitor;
    Dead_Code_Removal_Visitor *deadCodeRemovalVisitor;

    std::map<UIdent, Block *> block_code;
    std::map <UIdent, std::set<UIdent >> succ;
    std::map <UIdent, std::set<UIdent >> pred;

    UIdent current_block;

    explicit Optimization_Visitor(Program *program, Liveness_Visitor *livenessVisitor) : program(program),
                                                                                         livenessVisitor(
                                                                                                 livenessVisitor) {
        deadCodeRemovalVisitor = new Dead_Code_Removal_Visitor(program);
    }

    void eliminate_dead_code() {
        while (true) {
            deadCodeRemovalVisitor->removed_lines = 0;
            program->accept(deadCodeRemovalVisitor);
            if (deadCodeRemovalVisitor->removed_lines == 0) {
                break;
            }
            livenessVisitor->analyze_liveness_clear_init();
        }
    }

};