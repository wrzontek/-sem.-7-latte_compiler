#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include "Skeleton.C"
#include "Printer.H"
#include <filesystem>
#include <fstream>
#include <algorithm>

class String_Constant_Visitor : public Skeleton {
public:
    std::set <UIdent> string_constants;

    void visitAtomStr(AtomStr *atomStr) override {
        string_constants.insert(atomStr->string_);
    }
};

class Code_Generator : public Skeleton {
public:
    std::map <UIdent, std::set<UIdent >> &block_out_vars;
    std::map <UIdent, std::set<UIdent >> &block_in_vars;
    std::map <UIdent, std::set<UIdent >> &function_local_vars;

    UIdent current_block_name;
    UIdent current_function_name;
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

    UIdent const result_register = "_reg_eax";
    UIdent const stack_pointer = "_reg_esp";
    UIdent const base_pointer = "_reg_ebp";
//    std::set <UIdent> const general_registers = {"_reg_eax", "_reg_ebx"};
    std::set <UIdent> const general_registers = {"_reg_eax", "_reg_ecx", "_reg_edx",
                                                 "_reg_ebx", "_reg_esi", "_reg_edi"};
    std::set <UIdent> const preserved_registers = {"_reg_ebx", "_reg_esi", "_reg_edi"};
    std::set <UIdent> const volatile_registers = {"_reg_eax", "_reg_ecx", "_reg_edx"};

    std::set <UIdent> string_constants;

    UIdent register_lowest_byte(UIdent reg) {
        if (reg == "_reg_eax") {
            return "_reg_al";
        } else if (reg == "_reg_ecx") {
            return "_reg_cl";
        } else if (reg == "_reg_edx") {
            return "_reg_dl";
        } else if (reg == "_reg_ebx") {
            return "_reg_bl";
        } else if (reg == "_reg_esi") {
            return "_reg_sil";
        } else {
//            if (reg == "_reg_edi") {
            return "_reg_dil";
        }
    }

    // register to {variable}
    std::map <UIdent, std::set<UIdent>> register_values; // chyba jednoelementowy ten secik hehe

    // variable to: {
    //      register (_reg_r9)
    //      or memory location ("_d1_x" or "__arg_x"- then map this variable name to a location on the stack)
    //      or constant (123)
    // }
    std::map <UIdent, std::set<UIdent>> value_locations;
    std::set <UIdent> memory_slots;

    std::map <UIdent, UIdent> virtual_memory_to_real;
    std::map <UIdent, UIdent> string_constant_loc;

    ListNonJmpStmt::iterator block_stmt_iterator;
    ListNonJmpStmt::iterator list_stmt_end;

    int extra_stack_pushes;
    UIdent atom_var_name;
    std::ofstream output_file;
    Program *program;

    int offset_up;
    int offset_down;

    bool visiting_to_push_args;
    std::set <UIdent> call_out_vars;

    explicit Code_Generator(Program *program, const std::filesystem::path &file_path,
                            std::map <UIdent, std::set<UIdent >> &block_out_vars,
                            std::map <UIdent, std::set<UIdent >> &block_in_vars,
                            std::map <UIdent, std::set<UIdent >> &function_local_vars)
            : program(program), block_in_vars(block_in_vars), block_out_vars(block_out_vars),
              function_local_vars(function_local_vars) {
        output_file.open(file_path);
        if (!output_file.is_open()) {
            std::cerr << "can't open output file" << std::endl;
            exit(1);
        }
        auto string_constant_visitor = new String_Constant_Visitor();
        program->accept(string_constant_visitor);
        string_constants = string_constant_visitor->string_constants;
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
//        emitRaw("global main\nextern printInt\nextern printString\nextern error\nextern readInt\nextern readString\nextern stringsConcat\nextern stringsEqual\nextern stringsNotEqual\n\nsection .text\n");
        emitRaw(".intel_syntax noprefix\n");

        if (!string_constants.empty()) {
            emitRaw(".section  .rodata\n");
            int string_num = 0;
            for (auto string_constant: string_constants) {
                emitRaw(".SC" + std::to_string(string_num) + ":\n");
                string_constant_loc[string_constant] = ".SC" + std::to_string(string_num);

                std::string new_str;
                for (auto ch: string_constant) {
                    switch (ch) {
                        case '\'':
                            new_str += "\\'";
                            break;
                        case '\"':
                            new_str += "\\\"";
                            break;
                        case '\?':
                            new_str += "\\?";
                            break;
                        case '\\':
                            new_str += "\\\\";
                            break;
                        case '\a':
                            new_str += "\\a";
                            break;
                        case '\b':
                            new_str += "\\b";
                            break;
                        case '\f':
                            new_str += "\\f";
                            break;
                        case '\n':
                            new_str += "\\n";
                            break;
                        case '\r':
                            new_str += "\\r";
                            break;
                        case '\t':
                            new_str += "\\t";
                            break;
                        case '\v':
                            new_str += "\\v";
                            break;
                        default:
                            new_str += ch;
                    }
                }
                string_constant = "\"" + new_str + "\"";

                emitLine(".string " + string_constant);
                string_num++;
            }
        }

        emitRaw(".text\n.globl main\n");
        program->accept(this);
        if (!current_function_name.empty()) {
            emitRaw("\n");
        }
    }

    void close() {
        output_file.close();
    }

    void standardProlog() {
        // TODO nie działa jak jest coś puszowane wtrakcie funkcji
        for (auto preserved_register: preserved_registers) {
            emitLine("push " + preserved_register);
        }
        output_file << "\tpush ebp\n\tmov ebp, esp\n";
    }

    void standardEpilogue() {
        // restore preserved_registers
        output_file << "\tmov esp, ebp\n\tpop ebp\n";
        for (auto rit = preserved_registers.rbegin(); rit != preserved_registers.rend(); ++rit) {
            emitLine("pop " + (*rit));
        }
        output_file << "\tret\n";
    }

    void emitRaw(std::string content) {
        output_file << content;
    }

    void emitLine(std::string content) {
        std::size_t pos;
        std::string prefix = "_reg_";
        do {
            pos = content.find(prefix);
            if (pos != std::string::npos) {
                content.replace(pos, prefix.length(), "");
            }
        } while (pos != std::string::npos);

        output_file << "\t" + content + "\n";
    }

    bool block_is_function(UIdent ident) {
        return ident[0] != '_';
    }

    void visitBlock(Block *block) override {
        extra_stack_pushes = 0;
        current_block_name = block->uident_;
        if (block_is_function(current_block_name)) {
            if (!current_function_name.empty()) {
                emitRaw("\n");
            }

            current_function_name = current_block_name;
        }

        emitRaw(block->uident_ + ":\n");

        if (block_is_function(current_block_name)) {
            offset_down = 4;
            standardProlog();
            if (!function_local_vars[current_block_name].empty()) {
                emitLine("sub esp, " + std::to_string(
                        function_local_vars[current_block_name].size() * 4));
                for (auto var: function_local_vars[current_block_name]) {
                    virtual_memory_to_real[var] = "[ebp - " + std::to_string(offset_down) + "]";
                    offset_down += 4;
                }
            }

            if (!block_in_vars[current_block_name].empty()) {
                std::set<int> arg_nums;
                std::string arg_prefix = "__arg__";
                for (auto arg: block_in_vars[current_block_name]) {
                    arg_nums.insert(std::stoi(arg.substr(arg_prefix.length())));
                }

                offset_up = 20;
                for (auto arg_num: arg_nums) {
                    UIdent arg = arg_prefix + std::to_string(arg_num);
                    virtual_memory_to_real[arg] = "[ebp + " + std::to_string(offset_up) + "]";
                    offset_up += 4;
                }
            }
        }

        // na start bloku in_vars są w pamięci, rejestry wolne
        register_values.clear();
        value_locations.clear();
        memory_slots.clear();
        for (auto &in_var: block_in_vars[current_block_name]) {
            value_locations[in_var] = {in_var};
            memory_slots.insert(in_var);
        }

        if (!block->listnonjmpstmt_->empty()) block->listnonjmpstmt_->accept(this);

        for (auto &out_var: block_out_vars[current_block_name]) {
            auto &locs = value_locations[out_var];
            if (locs.find(out_var) == locs.end()) { // unwritten
                auto best_loc = get_best_location(locs);

                for (auto pair: value_locations) {
                    if (pair.first != out_var && pair.second.size() == 1 &&
                        pair.second.find(best_loc) != pair.second.end()) {
                        // żeby nie zamazało wartości które jest trzymana tylko tu
                        spill_to_memory(pair.first, best_loc);
                    }
                }

                if (is_variable(best_loc)) {
                    emitLine("MOV " + virtual_memory_to_real[out_var] + ", DWORD PTR " +
                             virtual_memory_to_real[best_loc]);
                } else if (is_const(best_loc)) {
                    emitLine("MOV " + virtual_memory_to_real[out_var] + ", DWORD PTR " + best_loc);
                } else {
                    emitLine("MOV " + virtual_memory_to_real[out_var] + ", " + best_loc);
                }
            }
        }

        block->listjmpstmt_->accept(this);
    }

    void visitListJmpStmt(ListJmpStmt *list_jmp_stmt) override {
        ListJmpStmt::iterator i = list_jmp_stmt->begin();
        (*i)->accept(this); // we only use the first jump stmt
    }

    void visitListNonJmpStmt(ListNonJmpStmt *list_stmt) override {
        block_stmt_iterator = list_stmt->begin();
        list_stmt_end = list_stmt->end();
        while (block_stmt_iterator != list_stmt_end) {
            (*block_stmt_iterator)->accept(this);
            ++block_stmt_iterator;
        }
    }

    void visitStmtRet(StmtRet *stmt) override {
        auto result_locs = get_atom_locations(stmt->atom_);
        for (auto &loc: result_locs) {
            if (loc == result_register) {
                // wynik jest w EAX, nic nie ma do roboty
                standardEpilogue();
                return;
            }
        }
        auto best_loc = get_best_location(result_locs);

        if (is_variable(best_loc)) {
            emitLine("MOV " + result_register + ", " + virtual_memory_to_real[best_loc]);
        } else {
            emitLine("MOV " + result_register + ", " + best_loc);
        }
        standardEpilogue();
    }

    void visitStmtVRet(StmtVRet *stmt) override {
        standardEpilogue();
    }

    std::set <UIdent> get_atom_locations(Atom *atom) {
        if (!atom->var_name().empty()) { // atom is variable
            return value_locations[atom->var_name()];
        } else if (atom->is_int_constant()) {
            return {atom->constant()};
        } else { // atom is string constant
            return {string_constant_loc[atom->constant()]};
        }
    }

    bool is_register(UIdent loc) {
        return loc.length() >= 5 && loc.substr(0, 5) == "_reg_";
    }

    bool is_variable(UIdent loc) {
        return !is_register(loc) && loc.length() >= 1 && loc.substr(0, 1) == "_";
    }

    bool is_string_constant(UIdent loc) {
        return loc.length() > 3 && loc.substr(0, 3) == ".SC";
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
                return loc; // constant (int or string)
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
        for (auto &reg: general_registers) {
            if (register_values.find(reg) == register_values.end()
                || register_values[reg].empty()) {
                return true;
            }
        }
        return false;
    }

    bool value_in_clean_register(UIdent value) {
        // register is clean if value is also present in some other place
        return value_locations[value].size() > 1;
    }

    UIdent get_latest_used_value_in_register() {
        auto block_stmt_iterator_copy = block_stmt_iterator;
        std::set <UIdent> values_in_registers;
        for (auto &pair: register_values) {
            for (auto &value: pair.second) {
                values_in_registers.insert(value);
            }
        }

        while (block_stmt_iterator_copy != list_stmt_end) {
            auto values_in_registers_before = values_in_registers;
            for (auto &used_var: (*block_stmt_iterator_copy)->use_vars) { values_in_registers.erase(used_var); }

            if (values_in_registers.size() == 1) {
                return (*values_in_registers.begin());
            } else if (values_in_registers.empty()) {
                auto val_tie_break_1 = *values_in_registers_before.begin();
                auto val_tie_break_2 = *(++values_in_registers_before.begin());

                if (value_in_clean_register(val_tie_break_1))
                    return val_tie_break_1;
                else
                    return val_tie_break_2;
            }

            ++block_stmt_iterator_copy;
        }

        return *values_in_registers.begin();
    }

    UIdent get_free_memory_slot() {
        for (auto memory_slot: memory_slots) {
            bool used = false;
            for (auto pair: value_locations) {
                if (pair.second.find(memory_slot) != pair.second.end()) {
                    used = true;
                    break;
                }
            }
            if (!used) {
                return memory_slot;
            }
        }
        return ""; // don't have free slot
    }

    UIdent put_constant_to_memory(UIdent constant) {
        auto free_memory_slot = get_free_memory_slot();
        if (!free_memory_slot.empty()) { // TODO to jest untested, może głupota
            emitLine("MOV [" + free_memory_slot + "], " + constant);
            return free_memory_slot;
        } else {
            emitLine("PUSH " + constant);

            auto pushed_loc = "__" + constant + "_p" + std::to_string(extra_stack_pushes);
            virtual_memory_to_real[pushed_loc] =
                    "[ebp - " + std::to_string(offset_down) + "]";
            memory_slots.insert(pushed_loc);

            extra_stack_pushes += 1;
            offset_down += 4;

            return pushed_loc;
        }
    }

    void spill_to_memory(UIdent value, UIdent value_current_loc) {
        auto free_memory_slot = get_free_memory_slot();
        if (!free_memory_slot.empty()) { // TODO to jest untested, może głupota
            value_locations[value] = {free_memory_slot};
            emitLine("MOV [" + free_memory_slot + "], " + value_current_loc);
        } else {
            if (is_variable(value_current_loc)) {
                emitLine("PUSH DWORD PTR " + virtual_memory_to_real[value_current_loc]);
            } else {
                emitLine("PUSH " + value_current_loc);
            }

            auto pushed_loc = value + "_p" + std::to_string(extra_stack_pushes);
            value_locations[value] = {pushed_loc};
            virtual_memory_to_real[pushed_loc] =
                    "[ebp - " + std::to_string(offset_down) + "]";
            memory_slots.insert(pushed_loc);

            extra_stack_pushes += 1;
            offset_down += 4;
        }
    }

    UIdent get_register_with_value(UIdent value) {
        for (auto &pair: register_values) {
            if (pair.second.find(value) != pair.second.end()) {
                return pair.first;
            }
        }
        exit(880);
    }

    UIdent get_free_register() {
        for (auto &reg: general_registers) {
            if (register_values.find(reg) == register_values.end()
                || register_values[reg].empty()) {
                return reg;
            }
        }

        UIdent latest_used_value = get_latest_used_value_in_register();
        // if latest_used_value register is dirty, spill to memory
        if (!value_in_clean_register(latest_used_value)) {
            spill_to_memory(latest_used_value, get_register_with_value(latest_used_value));
        }

        std::set <UIdent> cleared_registers;
        for (auto &pair: register_values) {
            if (pair.second.find(latest_used_value) != pair.second.end()) {
                // rejestry chyba tylko jedną wartość trzymają, jak nie to anlaki
                pair.second.clear();
                cleared_registers.insert(pair.first);
            }
        }
        for (auto &pair: value_locations) {
            for (auto &cleared_register: cleared_registers) {
                pair.second.erase(cleared_register); // nic nie znajduje się już w tych rejestrach
            }
        }

        return *cleared_registers.begin();
    }

    void force_clean_register(UIdent register_to_clean) {
        for (auto value: register_values[register_to_clean]) {
            if (!value_in_clean_register(value)) {
                spill_to_memory(value, register_to_clean);
            }
            value_locations[value].erase(register_to_clean);
        }
        register_values[register_to_clean].clear();
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
        }
    }

    void save_live_variable(UIdent variable_name, UIdent variable_location, std::set <UIdent> &out_vars) {
        if (is_live_variable(variable_name, out_vars) &&
            value_locations[variable_name].empty()) {
            if (have_free_register()) { // save B to some free register
                UIdent free_register = get_free_register();
                if (is_variable(variable_location)) {
                    emitLine("MOV " + free_register + ", " + virtual_memory_to_real[variable_location]);
                } else {
                    emitLine("MOV " + free_register + ", " + variable_location);
                }
                value_locations[variable_name].insert(free_register);
                register_values[free_register] = {variable_name};
            } else {
                spill_to_memory(variable_name, variable_location);
            }
        }
    }

    void visitStmtNoOp(StmtNoOp *stmt) override { // A := B
        if (stmt->uident_ == stmt->atom_->var_name()) { return; }
        UIdent R_register;

        auto B_location = get_best_location(get_atom_locations(stmt->atom_));
        auto B_variable_name = stmt->atom_->var_name();

        if (stmt->atom_->is_constant()) {
            value_locations[stmt->uident_] = {B_location};
            for (auto pair: register_values) {
                pair.second.erase(stmt->uident_);
            }

            forget_dead_variable(stmt->uident_, stmt->out_vars);
            return;
        } else if (is_register(B_location)) {
            R_register = B_location;
            value_locations[B_variable_name].erase(B_location);

            save_live_variable(B_variable_name, B_location, stmt->out_vars);

            register_values[R_register].erase(B_variable_name);
        } else {
            R_register = get_free_register();
            if (is_variable(B_location)) {
                save_live_variable(B_variable_name, B_location, stmt->out_vars);
                B_location = get_best_location(get_atom_locations(stmt->atom_));

                if (is_variable(B_location)) {
                    emitLine("MOV " + R_register + ", " + virtual_memory_to_real[B_location]);
                } else {
                    emitLine("MOV " + R_register + ", " + B_location);
                }
            } else {
                emitLine("MOV " + R_register + ", " + B_location);
            }
        }

        value_locations[stmt->uident_] = {R_register};
        register_values[R_register].insert(stmt->uident_);

        forget_dead_variable(stmt->atom_->var_name(), stmt->out_vars);
        forget_dead_variable(stmt->uident_, stmt->out_vars);
        return;
    }

    int get_power_of_two(Atom *atom) {
        if (!atom->is_int_constant()) {
            return -1;
        }
        int n = atom->get_int_constant();
        if (n <= 0) {
            return -1;
        }
        int i = 0;
        while (std::pow(2, i) <= n) {
            if (std::pow(2, i) == n) {
                return i;
            }
            ++i;
        }
        return -1;
    }

    void visitStmtBinOp(StmtBinOp *stmt) override { // A := B op C
        std::string instruction = stmt->binop_->instruction();
        auto lhs_location = get_best_location(get_atom_locations(stmt->atom_1));
        auto lhs_variable_name = stmt->atom_1->var_name();

        auto rhs_location = get_best_location(get_atom_locations(stmt->atom_2));
        UIdent R_register;
        bool lhs_rhs_are_same = lhs_location == rhs_location;

        if (is_string_constant(lhs_location)) {
            // TODO
            if (instruction == "ADD ") {}
            if (instruction == "CMP ") {}
            exit(444);
        }
/*        if (instruction == "IMUL " && (get_power_of_two(stmt->atom_1) != -1 || get_power_of_two(stmt->atom_2) != -1)) {
            // optymalizacja shiftleft
            // mov eax, A         ; Load A into eax
            // shl eax, B         ; Multiply eax by 2^B by shifting the bits to the left
            //return;
        }
        if (instruction == "IDIV " && !stmt->binop_->isModOp() && get_power_of_two(stmt->atom_2) != -1) {
            // optymalizacja shiftright
            // mov eax, A         ; Load A into eax
            // sar eax, B         ; Divide eax by 2^B by shifting the bits to the right
            //return;
        }
        if (instruction == "IDIV " && stmt->binop_->isModOp() && get_power_of_two(stmt->atom_2) != -1) {
            // optymalizacja modulo
            // mov eax, A         ; Load A into eax
            // and eax, B - 1     ; Mask out the bits that are not relevant to the result
            //return;
        }*/
        if (instruction == "ADD " || instruction == "SUB "
            || instruction == "IMUL " || instruction == "CMP ") {
            if (is_register(lhs_location)) {
                R_register = lhs_location;
                value_locations[lhs_variable_name].erase(lhs_location);

                if (stmt->uident_ != lhs_variable_name) {
                    save_live_variable(lhs_variable_name, lhs_location, stmt->out_vars);
                }
            } else {
                R_register = get_free_register();
                if (is_variable(lhs_location)) {
                    if (stmt->uident_ != lhs_variable_name) {
                        save_live_variable(lhs_variable_name, lhs_location, stmt->out_vars);
                    }
                    lhs_location = get_best_location(get_atom_locations(stmt->atom_1));

                    if (is_variable(lhs_location)) {
                        emitLine("MOV " + R_register + ", " + virtual_memory_to_real[lhs_location]);
                    } else {
                        emitLine("MOV " + R_register + ", " + lhs_location);
                    }
                } else {
                    emitLine("MOV " + R_register + ", " + lhs_location);
                }
            }

            if (lhs_rhs_are_same) { rhs_location = R_register; }
            if (is_variable(rhs_location)) {
                emitLine(instruction + R_register + ", DWORD PTR " + virtual_memory_to_real[rhs_location]);
            } else {
                emitLine(instruction + R_register + ", " + rhs_location);
            }
            if (instruction == "CMP ") {
                setCompareValue(stmt->binop_, R_register);
            }
            value_locations[stmt->uident_] = {R_register};
            register_values[R_register] = {stmt->uident_};

            forget_dead_variable(stmt->atom_1->var_name(), stmt->out_vars);
            forget_dead_variable(stmt->atom_2->var_name(), stmt->out_vars);
            forget_dead_variable(stmt->uident_, stmt->out_vars);
            return;
        }
        if (instruction == "IDIV ") { // div or mod
            auto b_locs = get_atom_locations(stmt->atom_1);
            if (b_locs.find("_reg_eax") == b_locs.end()) {
                // przenieść B do EAX
                force_clean_register("_reg_eax");
                if (is_variable(lhs_location)) {
                    emitLine("MOV _reg_eax, DWORD PTR " + virtual_memory_to_real[lhs_location]);
                } else {
                    emitLine("MOV _reg_eax, " + lhs_location);
                }
            }
            force_clean_register("_reg_edx");

            emitLine("CDQ");
            if (is_variable(rhs_location)) {
                emitLine("IDIV DWORD PTR" + virtual_memory_to_real[rhs_location]);
            } else {
                if (is_const(rhs_location)) {
                    rhs_location = put_constant_to_memory(rhs_location);
                    emitLine("IDIV DWORD PTR" + virtual_memory_to_real[rhs_location]);
                } else {
                    emitLine("IDIV " + rhs_location);
                }
            }

            R_register = stmt->binop_->isModOp() ? "_reg_edx" : "_reg_eax";
            value_locations[stmt->uident_] = {R_register};
            register_values[R_register] = {stmt->uident_};

            forget_dead_variable(stmt->atom_1->var_name(), stmt->out_vars);
            forget_dead_variable(stmt->atom_2->var_name(), stmt->out_vars);
            forget_dead_variable(stmt->uident_, stmt->out_vars);
            return;
        }
    }

    void setCompareValue(BinOp *binOp, UIdent R_register) {
        emitLine("MOV " + R_register + ", 0");
        emitLine(binOp->cond_set_instruction() + register_lowest_byte(R_register));
    }

    bool spillToFreePreservedRegister(UIdent value, UIdent current_register) {
        for (auto preserved_register: preserved_registers) {
            if (register_values.find(preserved_register) == register_values.end()
                || register_values[preserved_register].empty()) {
                emitLine("MOV " + preserved_register + ", " + current_register);
                register_values[preserved_register] = {value};
                value_locations[value].insert(preserved_register);
                return true;
            }
        }
        return false;
    }

    void saveVolatileRegisters() {
        for (auto volatile_register: volatile_registers) {
            for (auto value: register_values[volatile_register]) {
                // prefer spilling to preserved registers, otherwise to memory
                if (value_locations[value].size() <= 1) {
                    if (!spillToFreePreservedRegister(value, volatile_register)) {
                        spill_to_memory(value, volatile_register);
                    }
                }
                value_locations[value].erase(volatile_register);
            }
            register_values[volatile_register].clear();
        }
    }

    void visitListAtom(ListAtom *list) override {
        for (auto i = list->rbegin(); i != list->rend(); ++i) {
            if (visiting_to_push_args) {
                auto best_loc = get_best_location(get_atom_locations(*i));
                if (is_variable(best_loc)) {
                    emitLine("PUSH DWORD PTR " + virtual_memory_to_real[best_loc]);
                } else if (is_string_constant(best_loc)) {
                    emitLine("LEA eax, " + best_loc);
                    emitLine("PUSH eax");
                } else {
                    emitLine("PUSH " + best_loc);
                }
            } else { // visiting_to_clear_dead
                forget_dead_variable((*i)->var_name(), call_out_vars);
            }
        }
    }

    void visitStmtCall(StmtCall *stmt) override {
        auto value_locations_before_save = value_locations;
        saveVolatileRegisters();
        auto value_locations_after_save = value_locations;

        // to let pushes happen from better locations
        value_locations = value_locations_before_save;
        // push arguments to stack in reverse order
        visiting_to_push_args = true;
        stmt->listatom_->accept(this);

        value_locations = value_locations_after_save;

        // call function
        emitLine("CALL " + stmt->uident_2);
        value_locations[stmt->uident_1] = {"_reg_eax"};
        register_values["_reg_eax"] = {stmt->uident_1};
        if (stmt->listatom_->size() > 0) {
            emitLine("ADD esp, " + std::to_string(4 * stmt->listatom_->size()));
        }
        // clean dead variables
        call_out_vars = stmt->out_vars;
        visiting_to_push_args = false;
        stmt->listatom_->accept(this);
    }

    void visitStmtGoto(StmtGoto *stmt) override {
        emitLine("JMP " + stmt->uident_);
    }

    void visitStmtGoNext(StmtGoNext *stmt) override {} // nic nie robi

    void visitStmtCondJmp(StmtCondJmp *stmt) override {
        auto cond_location = get_best_location(get_atom_locations(stmt->atom_));
        if (is_variable(cond_location)) {
            emitLine("TEST DWORD PTR " + virtual_memory_to_real[cond_location] + ", DWORD PTR " +
                     virtual_memory_to_real[cond_location]);
        } else {
            emitLine("TEST " + cond_location + ", " + cond_location);
        }
        emitLine("JNZ " + stmt->uident_1);
        emitLine("JMP " + stmt->uident_2);
    }

};
