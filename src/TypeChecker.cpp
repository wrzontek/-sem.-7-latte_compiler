#include <string>
#include <iosfwd>
#include <iostream>
#include <set>
#include <vector>
#include "Absyn.H"
#include "Skeleton.C"

void throwError(int line_number, int char_number, std::string content) {
    std::cerr << "ERROR\n";
    std::cerr << "error at: " + std::to_string(line_number) + ", " + std::to_string(char_number) << std::endl;
    std::cerr << content << std::endl;
    exit(1);
}

struct CType {
    explicit CType(Ident name, std::vector<int> array_dims) : name(name), array_dims(array_dims) {}

    Ident name; // void, int, bool, string, <class>
    std::vector<int> array_dims; // empty if type is not array
};

struct CVar {
    explicit CVar(Ident name, CType *type) : name(name), type(type) {}

    Ident name;
    CType *type;
};

struct CFun {
    explicit CFun(Ident name, CType *return_type, std::vector<CVar *> args) : name(name), return_type(return_type),
                                                                              args(args) {}

    Ident name;
    CType *return_type;
    std::vector<CVar *> args;
};

struct CClass {
    Ident name;
    std::vector<CVar *> attributes;
    std::vector<CFun *> methods;
};

class Function_Def_Visitor : public Skeleton {
public:
    std::set<CFun *> &defined_functions;
    std::vector<CVar *> current_function_args;
    Ident current_arg_name;
    CType *current_type = nullptr;

    explicit Function_Def_Visitor(std::set<CFun *> &defined_functions) : defined_functions(defined_functions) {}

    void visitClassDef(ClassDef *class_def) override {};

    void visitClassExtendDef(ClassExtendDef *class_def) override {};
    // TODO pewnie można go też do klas użyć, dać mu mniejsze wycinki programu

    void visitFnDef(FnDef *fn_def) override {
        Ident name = fn_def->ident_;
        if (!fn_def->type_->canBeReturned()) {
            throwError(fn_def->line_number, fn_def->char_number, "invalid return type");
        }

        fn_def->type_->accept(this);
        CType *return_type = current_type;

        for (auto &def: defined_functions) {
            if (def->name == name) {
                throwError(fn_def->line_number, fn_def->char_number, "redefinition of function");
            }
        }

        current_function_args = std::vector<CVar *>();
        fn_def->listarg_->accept(this);
        defined_functions.insert(new CFun(name, return_type, current_function_args));

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
        arg->type_->accept(this);

        current_function_args.push_back(new CVar(current_arg_name, current_type));
    }

    void visitInt(Int *t) override {
        current_type = new CType(current_arg_name, std::vector<int>());
    }

};

class TypeChecker {
private:
    Program *program;
    std::set<CFun *> defined_functions;
    std::set<CClass *> defined_classes;
public:
    explicit TypeChecker(Program *program) : program(program) {
//        defined_functions.insert()
    }

    void checkCorrectness() {
        auto functionDefVisitor = new Function_Def_Visitor(defined_functions);
        program->accept(functionDefVisitor); // check duplicates (function names and arg names)
// crash if no main
//        program->accept(classDefVisitor);check duplicates (class names and member names)

    }
};