#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "StatementLivenessVisitor.cpp"

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

    explicit Liveness_Visitor(Program *program,
                              std::map <UIdent, std::set<UIdent>> &succ,
                              std::map <UIdent, std::set<UIdent>> &pred,
                              std::map<UIdent, Block *> &block_code)
            : program(program), succ(succ), pred(pred), block_code(block_code) {

        statementLivenessVisitor = new Statement_Liveness_Visitor();
        statementLivenessPrinter = new Statement_Liveness_Printer();
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

    void analyze_liveness() {
//        program->accept(statementLivenessVisitor);
//        program->accept(statementLivenessPrinter);

        for (auto pair: block_code) {
            auto block_name = pair.first;
            block_in_vars[block_name] = std::set<UIdent>();
            block_out_vars[block_name] = std::set<UIdent>();
        }
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

        program->accept(statementLivenessPrinter);
        std::cout << "\n\n\n";

        for (auto pair: block_code) {
            auto block_name = pair.first;
            auto block_in_vars_set = block_in_vars[block_name];
            auto block_out_vars_set = block_out_vars[block_name];

            std::cout << "\n\nBLOCK: " + block_name << std::endl;
            std::cout << "IN: ";
            printSet(block_in_vars_set);

            std::cout << "OUT: ";
            printSet(block_out_vars_set);
        }

    }
};

class Function_Local_Vars_Visitor : public Skeleton {
    // determines the variables that need stack allocation in each function
public:
    UIdent current_function;
    std::map <UIdent, std::set<UIdent >> function_local_vars;
    std::map <UIdent, std::set<UIdent >> &block_out_vars;

    bool is_function(UIdent ident) {
        return ident[0] != '_';
    }

    explicit Function_Local_Vars_Visitor(std::map <UIdent, std::set<UIdent >> &block_out_vars)
            : block_out_vars(block_out_vars) {}

    void visitBlock(Block *block) override {
        if (is_function(block->uident_)) {
            current_function = block->uident_;
        }

        function_local_vars[current_function].insert(block_out_vars[current_function].begin(),
                                                     block_out_vars[current_function].end());
    }
};