#include <string>
#include <vector>
#include "Absyn.H"
#include "Skeleton.C"
#include "Common.cpp"
#include "FunctionDefVisitor.cpp"
#include "ClassDefNameOnlyVisitor.cpp"
#include "ClassDefVisitor.cpp"
#include "TypeVisitor.cpp"

class TypeChecker {
private:
    Program *program;
    std::vector<CFun *> defined_functions;
    std::vector<CClass *> defined_classes;

    // for ordering the visits, first the parents then the children
    std::vector<ClassDef *> class_defs;
    std::vector<ClassExtendDef *> class_extend_defs;

    void checkNoIllegalExtend() {
        for (auto def: defined_classes) {
            if (!def->parent.empty()) {
                bool parent_defined = false;
                for (auto def2: defined_classes) {
                    if (def->parent == def2->name) parent_defined = true;
                }
                if (!parent_defined)
                    throwError("class " + def->name + " extends undefined class " + def->parent);
            }
        }
    }

    void checkMain() {
        bool defined = false;
        for (auto def: defined_functions) {
            if (def->name == "main") {
                if (!def->args.empty())
                    throwError("main function mustn't take arguments");
                if (def->return_type->name != "int" || !def->return_type->array_dims.empty())
                    throwError("main function must return int");

                defined = true;
            }
        }

        if (!defined)
            throwError("main function not defined");
    }

public:
    explicit TypeChecker(Program *program) : program(program) {
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

    void checkCorrectness() {
        auto classDefOnlyNameVisitor = new Class_Def_Name_Only_Visitor(defined_classes, class_defs, class_extend_defs);
        program->accept(classDefOnlyNameVisitor);
        checkNoIllegalExtend();

        auto functionDefVisitor = new Function_Def_Visitor(defined_functions, defined_classes);
        program->accept(functionDefVisitor); // check duplicates (function names and arg names)
        checkMain();

        auto classDefVisitor = new Class_Def_Visitor(defined_functions, defined_classes);
        for (auto def: class_defs) {
            def->accept(classDefVisitor);
        }

        auto classDefInitVisitor = new Class_Def_Init_Visitor(defined_functions, defined_classes);
        for (auto def: class_defs) {
            def->accept(classDefInitVisitor);
        }

        delete (classDefOnlyNameVisitor);
        delete (functionDefVisitor);
        delete (classDefVisitor);
        delete (classDefInitVisitor);
    }
};