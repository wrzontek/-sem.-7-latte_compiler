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
    explicit TypeChecker(Program *program) : program(program) {}

    void checkCorrectness() {
        auto classDefOnlyNameVisitor = new Class_Def_Name_Only_Visitor(defined_classes, class_defs, class_extend_defs);
        program->accept(classDefOnlyNameVisitor);
        checkNoIllegalExtend();

        auto defined_variables = std::vector<CVar *>();
        auto typeVisitor = new Type_Visitor(defined_classes, defined_variables);

        auto functionDefVisitor = new Function_Def_Visitor(defined_functions, defined_classes, typeVisitor);
        program->accept(functionDefVisitor); // check duplicates (function names and arg names)
        checkMain();

        auto classDefVisitor = new Class_Def_Visitor(defined_functions, defined_classes, typeVisitor);
        for (auto def: class_defs) {
            def->accept(classDefVisitor);
        }

        delete (classDefOnlyNameVisitor);
        delete (typeVisitor);
        delete (functionDefVisitor);
        delete (classDefVisitor);
    }
};