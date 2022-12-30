#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"

class CFG_Visitor : public Skeleton {
public:
    Program *program;

    std::map<UIdent, Block *> block_code;
    std::map <UIdent, std::set<UIdent >> succ;
    std::map <UIdent, std::set<UIdent >> pred;

    UIdent current_block;

    explicit CFG_Visitor(Program *program) : program(program) {}

    void visitBlock(Block *block) override {
        current_block = block->uident_;
        block_code[current_block] = block;
        block->listjmpstmt_->accept(this);
    }

    void visitStmtGoto(StmtGoto *stmt) override {
        succ[current_block].insert(stmt->uident_);
    }

    void visitStmtGoNext(StmtGoNext *stmt) override {
        succ[current_block].insert(stmt->uident_);
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        succ[current_block].insert(stmt->uident_1);
        succ[current_block].insert(stmt->uident_2);
    }

    void setPred() {
        for (auto pair: succ) {
            auto from = pair.first;
            for (auto to: pair.second) {
                pred[to].insert(from);
            }
        }
    }

    void printSucc() {
        for (auto pair: succ) {
            std::cout << "FROM " + pair.first << std::endl;
            for (auto label: pair.second) {
                std::cout << "\t" + label << std::endl;
            }
        }
    }

    void printPred() {
        for (auto pair: pred) {
            std::cout << "TO " + pair.first << std::endl;
            for (auto label: pair.second) {
                std::cout << "\t" + label << std::endl;
            }
        }
    }

};