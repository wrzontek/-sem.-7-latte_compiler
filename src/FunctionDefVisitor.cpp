#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"
#include "TypeVisitor.cpp"

class Function_Def_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_functions;
    std::vector<CClass *> &defined_classes;
    std::vector<CVar *> current_function_args;

    Ident current_arg_name;
    CType *current_type = nullptr;

    explicit Function_Def_Visitor(std::vector<CFun *> &defined_functions, std::vector<CClass *> &defined_classes, Type_Visitor *typeVisitor)
            : defined_functions(defined_functions), defined_classes(defined_classes) ,typeVisitor(typeVisitor) {
        std::vector<CVar*> printIntArgs;
        printIntArgs.push_back(new CVar("arg", new CType("int", std::vector<int>())));
        defined_functions.push_back(new CFun(
                std::string("printInt"),
                new CType("void", std::vector<int>()),
                printIntArgs));

        std::vector<CVar*> printStringArgs;
        printStringArgs.push_back(new CVar("arg", new CType("string", std::vector<int>())));
        defined_functions.push_back(new CFun(
                "printString",
                new CType("void", std::vector<int>()),
                printStringArgs));

        defined_functions.push_back(new CFun(
                "error",
                new CType("void", std::vector<int>()),
                std::vector<CVar*>()));

        defined_functions.push_back(new CFun(
                "readString",
                new CType("string", std::vector<int>()),
                std::vector<CVar*>()));
    }

    void visitClassDef(ClassDef *class_def) override {};

    void visitClassExtendDef(ClassExtendDef *class_def) override {};
    // TODO pewnie można go też do klas użyć, dać mu mniejsze wycinki programu

    void visitFnDef(FnDef *fn_def) override {
        Ident name = fn_def->ident_;
        if (!fn_def->type_->canBeReturned()) {
            throwError(fn_def->line_number, fn_def->char_number, "invalid return type"); // w sumie to chyba dowolny typ może być ale niech zostanie
        }

        CType *return_type = typeVisitor->getType(fn_def->type_);

        for (auto &def: defined_functions) {
            if (def->name == name) {
                throwError(fn_def->line_number, fn_def->char_number, "redefinition of function");
            }
        }

        current_function_args = std::vector<CVar *>();
        fn_def->listarg_->accept(this);
        defined_functions.push_back(new CFun(name, return_type, current_function_args));

        current_function_args.clear();
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

        current_function_args.push_back(new CVar(
                current_arg_name,
                typeVisitor->getType(arg->type_)));
    }
};