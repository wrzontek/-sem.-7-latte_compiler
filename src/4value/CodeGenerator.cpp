#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Skeleton.C"
#include "Printer.H"
#include <filesystem>
#include <fstream>

class Code_Generator : public Skeleton {
public:
    std::map <UIdent, std::set<UIdent >> &block_out_vars;
    std::map <UIdent, std::set<UIdent >> &block_in_vars;
    UIdent current_block_name;

    UIdent result_register = "_reg_rax";
    UIdent stack_pointer = "_reg_rsp";
    UIdent base_pointer = "_reg_rbp";
    std::set <UIdent> general_registers = {//"_reg_rax", "_reg_rsp","_reg_rbp",
            "_reg_rcx", "_reg_rdx", "_reg_rbx", "_reg_rsi",
            "_reg_rdi", "_reg_r8", "_reg_r9", "_reg_r10",
            "_reg_r11", "_reg_r12", "_reg_r13", "_reg_r14",
            "_reg_r15"};

    std::map <UIdent, std::set<UIdent>> register_values;

    // register (_reg_r9)
    // or memory location ("_d1_x" or "__arg_x"- then map this variable name to a location on the stack)
    // or constant (123) TODO FOR NOW ONLY INTEGER
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

    void generate() {
        program->accept(this);
    }

    void close() {
        output_file.close();
    }

    void emitRaw(std::string content) {
        output_file << content;
    }

    void emitLine(std::string content) {
        output_file << "\t" + content + "\n";
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

    void visitStmtInc(StmtInc *stmt) override {}

    void visitStmtDecr(StmtDecr *stmt) override {}

    std::set <UIdent> get_atom_locations(Atom *atom) {
        if (!atom->var_name().empty()) { // atom is variable
            return value_locations[atom->var_name()];
        } else { // atom is constant TODO FOR NOW ONLY INTEGER
            return {atom->constant()};
        }
    }

    UIdent get_best_location(std::set <UIdent> locations) {
        UIdent register_;
        UIdent memory;

        for (UIdent loc: locations) {
            if (loc.length() >= 5 && loc.substr(5) == "_reg_") {
                register_ = loc;
            } else if (loc.length() >= 1 && loc.substr(1) == "_") {
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

    UIdent get_free_register() {
        return "_reg_r15"; //TODO
    }

/*
 *  r0 = [a]
 *  r0 -= [b]
*/
    void visitStmtNoOp(StmtNoOp *stmt) override {
        value_locations[stmt->uident_] = get_atom_locations(stmt->atom_);
    }

    void visitStmtNegOp(StmtNegOp *stmt) override {}

    void visitStmtBinOp(StmtBinOp *stmt) override {
        std::string instruction = stmt->binop_->instruction();
        if (instruction == "ADD " || instruction == "SUB ") {
            UIdent result_register = get_free_register();

            // ładujemy LHS do result_register, preferencje: stała>rejestr>pamięć
            auto lhs_location = get_best_location(get_atom_locations(stmt->atom_1));
            emitLine("MOV " + result_register + ", " + lhs_location);

            // dodajemy RHS do result_register, preferencje: stała>rejestr>pamięć
            auto rhs_location = get_best_location(get_atom_locations(stmt->atom_2));
            emitLine(instruction + result_register + ", " + rhs_location);
        } else {
            //TODO
            exit(124);
        }
    }

    void visitStmtCall(StmtCall *stmt) override {}

};
