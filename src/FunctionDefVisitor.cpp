#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"
#include "TypeVisitor.cpp"

class Function_Def_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_functions; // global or class methods if used in class
    std::vector<CClass *> &defined_classes;
    std::vector<CVar *> current_function_args;

    Ident current_arg_name;
    CType *current_type = nullptr;

    explicit Function_Def_Visitor(std::vector<CFun *> &defined_functions, std::vector<CClass *> &defined_classes)
            : defined_functions(defined_functions), defined_classes(defined_classes) {}

    void visitClassDef(ClassDef *class_def) override {};

    void visitClassExtendDef(ClassExtendDef *class_def) override {};

    void visitFunctionDefinition(Ident name, Type *return_type, ListArg *listarg, int line_number, int char_number,
                                 bool is_method) {
        if (!return_type->canBeReturned()) {
            throwError(line_number, char_number,
                       "invalid return type"); // w sumie to chyba dowolny typ może być ale niech zostanie
        }

        typeVisitor = new Type_Visitor(defined_classes, std::vector<CVar *>(), defined_functions);
        CType *creturn_type = typeVisitor->getType(return_type);
        delete (typeVisitor);

        for (auto &def: defined_functions) {
            if (def->name == name) {
                throwError(line_number, char_number,
                           "redefinition of " + std::string(is_method ? "method" : "function"));
            }
        }

        current_function_args = std::vector<CVar *>();
        listarg->accept(this);
        defined_functions.push_back(new CFun(name, creturn_type, current_function_args));

        current_function_args.clear();
    }

    void visitFnDef(FnDef *fn_def) override {
        visitFunctionDefinition(fn_def->ident_, fn_def->type_, fn_def->listarg_, fn_def->line_number,
                                fn_def->char_number, false);
    };

    void visitMethodMember(MethodMember *fn_def) override {
        visitFunctionDefinition(fn_def->ident_, fn_def->type_, fn_def->listarg_, fn_def->line_number,
                                fn_def->char_number, true);
    };

    void visitAr(Ar *arg) override {
        Ident name = arg->ident_;
        for (auto &def: current_function_args) {
            if (def->name == name) {
                throwError(arg->line_number, arg->char_number, "redefinition of argument");
            }
        }

        if (!arg->type_->canBeArg()) { // np void nie może być
            throwError(arg->line_number, arg->char_number, "invalid argument type");
        }

        current_arg_name = arg->ident_;
        typeVisitor = new Type_Visitor(defined_classes, std::vector<CVar *>(), defined_functions);
        CType *arg_type = typeVisitor->getType(arg->type_);
        delete (typeVisitor);

        current_function_args.push_back(new CVar(
                current_arg_name,
                arg_type));
    }
};