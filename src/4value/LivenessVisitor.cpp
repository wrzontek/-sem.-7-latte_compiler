#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "StatementLivenessVisitor.cpp"

class Liveness_Visitor : public Skeleton {
public:
    Program *program;

    std::map<UIdent, Block *> &block_code;
    std::map <UIdent, std::set<UIdent >> &succ;
    std::map <UIdent, std::set<UIdent >> &pred;

    std::map <UIdent, std::set<UIdent >> block_out_vars;
    std::map <UIdent, std::set<UIdent >> block_in_vars;

    Statement_Liveness_Visitor *statementLivenessVisitor;
    Statement_Liveness_Printer *statementLivenessPrinter;

    explicit Liveness_Visitor(Program *program,
                              std::map <UIdent, std::set<UIdent>> &succ,
                              std::map <UIdent, std::set<UIdent>> &pred,
                              std::map<UIdent, Block *> &block_code)
            : program(program), succ(succ), pred(pred), block_code(block_code) {

        statementLivenessVisitor = new Statement_Liveness_Visitor();
        statementLivenessPrinter = new Statement_Liveness_Printer();
    }

    void analyze_liveness() {
//        program->accept(statementLivenessVisitor);
//        program->accept(statementLivenessPrinter);

        for (auto pair: block_code) {
            auto block_name = pair.first;
            block_in_vars[block_name] = std::set<UIdent>();
            block_out_vars[block_name] = std::set<UIdent>();
        }
        for (auto pair: block_code) {
            auto block_name = pair.first;
            auto block_code = pair.second;
            auto block_in_vars_before = block_in_vars[block_name];
            auto block_out_vars_before = block_out_vars[block_name];

            statementLivenessVisitor->current_stmt_out_vars = block_out_vars_before;
            block_code->accept(statementLivenessVisitor);
        }
    }


};