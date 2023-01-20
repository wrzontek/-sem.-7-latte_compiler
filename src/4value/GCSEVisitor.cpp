#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "StatementGCSEVisitor.cpp"

class GCSE_Visitor {
public:
    bool changed;

    Program *program;

    std::map<UIdent, Block *> &block_code;
    std::map <UIdent, std::set<UIdent >> &succ;
    std::map <UIdent, std::set<UIdent >> &pred;

    std::map <UIdent, std::vector<Expression *>> block_out_const_exprs;

    Statement_GCSE_Visitor *statementGCSEVisitor;

    explicit GCSE_Visitor(Program *program,
                          std::map <UIdent, std::set<UIdent>> &succ,
                          std::map <UIdent, std::set<UIdent>> &pred,
                          std::map<UIdent, Block *> &block_code)
            : program(program), succ(succ), pred(pred), block_code(block_code) {

        statementGCSEVisitor = new Statement_GCSE_Visitor();
    }

    void reset() {
        changed = false;
        statementGCSEVisitor->changed = false;
    }

    void printSet(std::vector <Expression *> &set) {
        std::cout << "{";
        for (auto it = set.begin(); it != set.end(); ++it) {
            if (it != set.begin()) {
                std::cout << ", ";
            }
            std::cout << (*it)->assignment_to;
        }
        std::cout << "}" << std::endl;
    }

    void run_gcse() {
        statementGCSEVisitor->changed = false;
        statementGCSEVisitor->replace_code = false;
        for (auto pair: block_code) {
            auto block_name = pair.first;
            block_out_const_exprs[block_name] = {};
        }
        run_gcse_no_init();
    }

    void run_gcse_no_init() {
        while (true) {
            int equal_count = 0;
            for (auto pair: block_code) {
                auto block_name = pair.first;
                auto block_code = pair.second;
                auto block_out_const_exprs_before = block_out_const_exprs[block_name];
                std::vector<Expression *> block_in_const_expr = {};

                bool first = true;
                for (auto pred: pred[block_name]) {
                    if (first) {
                        block_in_const_expr = block_out_const_exprs[pred];
                        first = false;
                    } else {
                        block_in_const_expr = intersection(block_in_const_expr, block_out_const_exprs[pred]);
                    }
                }
//                std::cout << "\n" + block_name << std::endl;
//                printSet(block_in_const_expr);

                statementGCSEVisitor->current_const_exprs = block_in_const_expr;
                block_code->accept(statementGCSEVisitor);
                block_out_const_exprs[block_name] = statementGCSEVisitor->current_const_exprs;

                if (block_out_const_exprs_before.size() == block_out_const_exprs[block_name].size()) {
//                    std::cout << "equal " + block_name << std::endl;
                    equal_count++;
                }
//                else {
//                    std::cout << "\n" + block_name << std::endl;
//                    printSet(block_out_const_exprs[block_name]);
//                    printSet(block_out_const_exprs_before);
//                }
            }
            if (statementGCSEVisitor->replace_code) {
                break;
            }
            if (equal_count == block_code.size())
                statementGCSEVisitor->replace_code = true;
        }
        changed = statementGCSEVisitor->changed;
    }

};