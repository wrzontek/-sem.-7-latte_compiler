#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "StatementLivenessVisitor.cpp"

class Liveness_Clear_Visitor : public Skeleton {
public:
    Program *program;

    explicit Liveness_Clear_Visitor(Program *program) : program(program) {}

    void clear_liveness(NonJmpStmt *stmt) {
        stmt->in_vars = {};
        stmt->out_vars = {};
        stmt->use_vars = {};
        stmt->kill_vars = {};
    }

    void clear_liveness(JmpStmt *stmt) {
        stmt->in_vars = {};
        stmt->out_vars = {};
        stmt->use_vars = {};
        stmt->kill_vars = {};
    }

    void visitStmtGoNext(StmtGoNext *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtGoto(StmtGoto *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtRet(StmtRet *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtVRet(StmtVRet *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtDoNothing(StmtDoNothing *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtNoOp(StmtNoOp *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtBinOp(StmtBinOp *stmt) override {
        clear_liveness(stmt);
    }

    void visitStmtCall(StmtCall *stmt) override {
        clear_liveness(stmt);
    }

};

class Liveness_Visitor {
public:
    Program *program;

    std::map<UIdent, Block *> &block_code;
    std::map <UIdent, std::set<UIdent >> &succ;
    std::map <UIdent, std::set<UIdent >> &pred;

    std::map <UIdent, std::set<UIdent >> block_out_vars;
    std::map <UIdent, std::set<UIdent >> block_in_vars;

    Statement_Liveness_Visitor *statementLivenessVisitor;
    Statement_Liveness_Printer *statementLivenessPrinter;
    Liveness_Clear_Visitor *livenessClearVisitor;

    explicit Liveness_Visitor(Program *program,
                              std::map <UIdent, std::set<UIdent>> &succ,
                              std::map <UIdent, std::set<UIdent>> &pred,
                              std::map<UIdent, Block *> &block_code)
            : program(program), succ(succ), pred(pred), block_code(block_code) {

        statementLivenessVisitor = new Statement_Liveness_Visitor();
        statementLivenessPrinter = new Statement_Liveness_Printer();
        livenessClearVisitor = new Liveness_Clear_Visitor(program);
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

    void analyze_liveness_clear_init() {
        program->accept(livenessClearVisitor);
        analyze_liveness();
    }

    void analyze_liveness() {
        for (auto pair: block_code) {
            auto block_name = pair.first;
            block_in_vars[block_name] = std::set<UIdent>();
            block_out_vars[block_name] = std::set<UIdent>();
        }
        analyze_liveness_no_init();
    }

    void analyze_liveness_no_init() {
        while (true) {
            int equal_count = 0;
            for (auto pair: block_code) {
                auto block_name = pair.first;
                auto block_code = pair.second;
                auto block_in_vars_before = block_in_vars[block_name];
                auto block_out_vars_before = block_out_vars[block_name];

                statementLivenessVisitor->current_stmt_out_vars = block_out_vars_before;
                block_code->accept(statementLivenessVisitor);
                block_in_vars[block_name] = statementLivenessVisitor->block_in_vars;

                std::set <UIdent> out_vars;
                for (auto successor: succ[block_name]) {
                    out_vars.insert(block_in_vars[successor].begin(), block_in_vars[successor].end());
                }
                block_out_vars[block_name] = out_vars;

                if (block_in_vars_before == block_in_vars[block_name] &&
                    block_out_vars_before == block_out_vars[block_name]) {
                    equal_count++;
                }
            }
            if (equal_count == block_code.size())
                break;
        }
//        program->accept(statementLivenessPrinter);
    }
//        std::cout << "\n\n\n";
//
//        for (auto pair: block_code) {
//            auto block_name = pair.first;
//            auto block_in_vars_set = block_in_vars[block_name];
//            auto block_out_vars_set = block_out_vars[block_name];
//
//            std::cout << "\n\nBLOCK: " + block_name << std::endl;
//            std::cout << "IN: ";
//            printSet(block_in_vars_set);
//
//            std::cout << "OUT: ";
//            printSet(block_out_vars_set);
//        }


};

class Function_Local_Vars_Visitor : public Skeleton {
    // determines the variables that need stack allocation in each function
public:
    UIdent current_function;
    std::map <UIdent, std::set<UIdent >> function_local_vars;
    std::map <UIdent, std::set<UIdent >> &block_out_vars;
    std::set <UIdent> functions_with_string_result = {"_stringsConcat", "readString"};

    bool block_is_string_ret_function(UIdent ident) {
        return ident.length() >= 5 && ident.substr(0, 5) == "_str_";
    }

    bool block_is_function(UIdent ident) {
        return block_is_string_ret_function(ident) || ident[0] != '_';
    }

    explicit Function_Local_Vars_Visitor(std::map <UIdent, std::set<UIdent >> &block_out_vars)
            : block_out_vars(block_out_vars) {}

    void visitBlock(Block *block) override {
        if (block_is_function(block->uident_)) {
            current_function = block->uident_;
            if (block_is_string_ret_function(block->uident_)) {
                functions_with_string_result.insert(block->uident_.substr(5));
            }
        }

        function_local_vars[current_function].insert(block_out_vars[block->uident_].begin(),
                                                     block_out_vars[block->uident_].end());

        block->listjmpstmt_->accept(this);
        block->listnonjmpstmt_->accept(this);
    }
};