#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "Printer.H"
#include <filesystem>
#include <fstream>
#include <algorithm>

class Code_Generator : public Skeleton {
public:
    std::map <UIdent, std::set<UIdent >> &block_out_vars;
    std::map <UIdent, std::set<UIdent >> &block_in_vars;
    UIdent current_block_name;
/*
    UIdent result_register = "_reg_rax";
    UIdent stack_pointer = "_reg_rsp";
    UIdent base_pointer = "_reg_rbp";
    std::set <UIdent> general_registers = {//"_reg_rax", "_reg_rsp","_reg_rbp",
            "_reg_rcx", "_reg_rdx", "_reg_rbx", "_reg_rsi",
            "_reg_rdi", "_reg_r8", "_reg_r9", "_reg_r10",
            "_reg_r11", "_reg_r12", "_reg_r13", "_reg_r14",
            "_reg_r15"};
*/

    UIdent result_register = "_reg_eax";
    UIdent stack_pointer = "_reg_esp";
    UIdent base_pointer = "_reg_ebp";
    std::set <UIdent> general_registers = {"_reg_eax", "_reg_ecx", "_reg_edx",
                                           "_reg_ebx", "_reg_esi", "_reg_edi"};


    // register to {variable}
    std::map <UIdent, std::set<UIdent>> register_values;

    // variable to: {
    //      register (_reg_r9)
    //      or memory location ("_d1_x" or "__arg_x"- then map this variable name to a location on the stack)
    //      or constant (123) TODO FOR NOW ONLY INTEGER
    // }
    std::map <UIdent, std::set<UIdent>> value_locations;


    UIdent atom_var_name;
    std::ofstream output_file;
    Program *program;

    explicit Code_Generator(Program *program, const std::filesystem::path &file_path,
                            std::map <UIdent, std::set<UIdent >> &block_out_vars,
                            std::map <UIdent, std::set<UIdent >> &block_in_vars)
            : program(program), block_in_vars(block_in_vars), block_out_vars(block_out_vars) {
        output_file.open(file_path);
        if (!output_file.is_open()) {
            std::cerr << "can't open output file" << std::endl;
            exit(1);
        }
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

    void generate() {
        program->accept(this);
    }

    void close() {
        output_file.close();
    }

    void emitRaw(std::string content) {
        output_file << content;
        std::cerr << content;
    }

    void emitLine(std::string content) {
        output_file << "\t" + content + "\n";
        std::cerr << "\t" + content + "\n";
    }

    void visitBlock(Block *block) override {
        current_block_name = block->uident_;
        // na start bloku in_vars są w pamięci, rejestry wolne
        register_values.clear();
        value_locations.clear();
        for (auto in_var: block_in_vars[current_block_name]) {
            value_locations[in_var] = {in_var};
        }

        if (!block->listnonjmpstmt_->empty()) block->listnonjmpstmt_->accept(this);

        // TODO At the end of the block write all live, but yet unwritten values
//        for (auto out_var: block_out_vars[current_block_name]) {
//        }
        block->listjmpstmt_->accept(this);
    }

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        (*i)->accept(this); // we only use the first jump stmt
    }

    void visitListNonJmpStmt(ListNonJmpStmt *list_stmt) override {
        for (ListNonJmpStmt::iterator i = list_stmt->begin(); i != list_stmt->end(); ++i) {
            (*i)->accept(this);
        }
    }

    void visitStmtCondJmp(StmtCondJmp *stmt) override {}

    void visitStmtRet(StmtRet *stmt) override {}

    std::set <UIdent> get_atom_locations(Atom *atom) {
        if (!atom->var_name().empty()) { // atom is variable
            return value_locations[atom->var_name()];
        } else { // atom is constant TODO FOR NOW ONLY INTEGER
            return {atom->constant()};
        }
    }

    bool is_register(UIdent loc) {
        return loc.length() >= 5 && loc.substr(0, 5) == "_reg_";
    }

    bool is_variable(UIdent loc) {
        return !is_register(loc) && loc.length() >= 1 && loc.substr(0, 1) == "_";
    }

    bool is_const(UIdent loc) {
        return !is_register(loc) && !is_variable(loc);
    }

//    preferencje: stała > rejestr > pamięć
    UIdent get_best_location(std::set <UIdent> locations) {
        UIdent register_;
        UIdent memory;

        for (UIdent loc: locations) {
            if (is_register(loc)) {
                register_ = loc;
            } else if (is_variable(loc)) {
                memory = loc;
            } else {
                return loc; // constant
            }
        }

        if (!register_.empty()) {
            return register_;
        } else if (!memory.empty()) {
            return memory;
        } else {
            exit(667);
        }
    }

    bool have_free_register() {
        for (auto reg: general_registers) {
            if (register_values.find(reg) == register_values.end()
                || register_values[reg].empty()) {
                return true;
            }
        }
        return false;
    }

    UIdent get_free_register() {
        for (auto reg: general_registers) {
            if (register_values.find(reg) == register_values.end()
                || register_values[reg].empty()) {
                return reg;
            }
        }
        // TODO SPILLING
        std::cout << "\nREGISTER SPILLING\n";
        exit(123);
    }

    bool is_live_variable(UIdent var, const std::set <UIdent> &out_vars) {
        return !var.empty() && // it is in fact a variable, not constant
               out_vars.find(var) != out_vars.end(); // is alive after quadruple
    }

    bool is_dead_variable(UIdent var, const std::set <UIdent> &out_vars) {
        return !var.empty() && // it is in fact a variable, not constant
               out_vars.find(var) == out_vars.end(); // is dead after quadruple
    }

    void forget_dead_variable(UIdent var, const std::set <UIdent> &out_vars) {
        if (is_dead_variable(var, out_vars)) { // is dead after quadruple
            value_locations.erase(var);

            for (auto &pair: register_values) {
                auto &values = pair.second;
                values.erase(var);
            }

            // ? jakaś zmienna może być zapisana pod miejscem w pamięci dla umierającej zmiennej, zostawmy ją
//            for (auto &pair: value_locations) {
//                auto &locations = pair.second;
//                locations.erase(var);
//            }
        }
    }

    void save_live_variable(UIdent variable_name, UIdent variable_location, std::set <UIdent> &out_vars) {
//        if (variable_name != stmt->uident_) {
        if (is_live_variable(variable_name, out_vars) &&
            value_locations[variable_name].empty()) { // todo to potencjalnie można lepiej?
            if (have_free_register()) { // save B to some free register
                UIdent free_register = get_free_register();
                emitLine("MOV " + free_register + ", " + variable_location);

                value_locations[variable_name].insert(free_register);
                register_values[free_register] = {variable_name};
            } else { // push B to memory
                std::cout << "\nTODO push variable_name to memory\n";
                exit(123);
            }
        } else if (!is_live_variable(variable_name, out_vars)) {
            forget_dead_variable(variable_name, out_vars);
        }
    }

    void visitStmtNoOp(StmtNoOp *stmt) override { // A := B
        UIdent result_register;

        auto B_location = get_best_location(get_atom_locations(stmt->atom_));
        auto B_variable_name = stmt->atom_->var_name();
//        std::cout << "LOCATION B " + B_location + " for " + B_variable_name << std::endl;

        if (is_register(B_location)) {
            result_register = B_location;
            value_locations[B_variable_name].erase(B_location);

            save_live_variable(B_variable_name, B_location, stmt->out_vars);

            register_values[result_register].erase(B_variable_name);
        } else {
            result_register = get_free_register();
            if (is_variable(B_location)) {
                save_live_variable(B_variable_name, "[" + B_location + "]", stmt->out_vars);
                B_location = get_best_location(get_atom_locations(stmt->atom_));

                if (is_variable(B_location)) {
                    emitLine("MOV " + result_register + ", [" + B_location + "]");
                } else {
                    emitLine("MOV " + result_register + ", " + B_location);
                }
            } else {
                emitLine("MOV " + result_register + ", " + B_location);
            }
        }

        value_locations[stmt->uident_] = {result_register};
        register_values[result_register].insert(stmt->uident_);

        forget_dead_variable(stmt->atom_->var_name(), stmt->out_vars);
        forget_dead_variable(stmt->uident_, stmt->out_vars); // ??
        return;
    }

    void visitStmtBinOp(StmtBinOp *stmt) override { // A := B op C
        std::string instruction = stmt->binop_->instruction();
        if (instruction == "ADD " && stmt->atom_1->is_string()) {
            // TODO
            exit(444);
        }

        if (instruction == "ADD " || instruction == "SUB ") {
            UIdent result_register;
//            std::cout << "LOCS FOR: " + stmt->atom_1->var_name() << std::endl;
//            printSet(get_atom_locations(stmt->atom_1));

            auto lhs_location = get_best_location(get_atom_locations(stmt->atom_1));
            auto b_variable_name = stmt->atom_1->var_name();
//            std::cout << "LOCATION L " + lhs_location + " for " + b_variable_name << std::endl;

            if (is_register(lhs_location)) {
                result_register = lhs_location;
                value_locations[b_variable_name].erase(lhs_location);

                save_live_variable(b_variable_name, lhs_location, stmt->out_vars);
            } else {
                result_register = get_free_register();
                if (is_variable(lhs_location)) {
                    save_live_variable(b_variable_name, "[" + lhs_location + "]", stmt->out_vars);
                    lhs_location = get_best_location(get_atom_locations(stmt->atom_1));

                    if (is_variable(lhs_location)) {
                        emitLine("MOV " + result_register + ", [" + lhs_location + "]");
                    } else {
                        emitLine("MOV " + result_register + ", " + lhs_location);
                    }
                } else {
                    emitLine("MOV " + result_register + ", " + lhs_location);
                }
            }

            // dodajemy RHS do result_register
            auto rhs_location = get_best_location(get_atom_locations(stmt->atom_2));
//            std::cout << "LOCATION R " + rhs_location + " for " + stmt->atom_2->var_name() << std::endl;
//            std::cout << std::endl;

            if (is_variable(rhs_location)) {
                emitLine(instruction + result_register + ", [" + rhs_location + "]");
            } else {
                emitLine(instruction + result_register + ", " + rhs_location);
            }
            value_locations[stmt->uident_] = {result_register};
            register_values[result_register] = {stmt->uident_};

            forget_dead_variable(stmt->atom_2->var_name(), stmt->out_vars);
            return;
        }

        //TODO "CMP " , mulop, divop, modop
        exit(124);
    }

    void visitStmtCall(StmtCall *stmt) override {}

};
