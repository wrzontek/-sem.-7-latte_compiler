#include <string>
#include <vector>
#include "Absyn.H"
#include "Skeleton.C"
#include "Common.cpp"
#include "FunctionDefVisitor.cpp"
#include "ClassDefNameOnlyVisitor.cpp"
#include "ClassDefVisitor.cpp"
#include "TypeVisitor.cpp"
#include "FunctionBodyVisitor.cpp"

class TypeChecker {
private:
    Program *program;
    std::vector<CFun *> defined_functions;
    std::vector<CClass *> defined_classes;
    std::set <Ident> defined_class_idents;

    // for ordering the visits, first the parents then the children
    std::vector<ClassDef *> class_defs;
    std::vector<ClassExtendDef *> class_extend_defs;

    void checkNoIllegalExtend() {
        for (auto def: defined_classes) {
            if (!def->parent_name.empty()) {
                bool parent_defined = false;
                for (auto def2: defined_classes) {
                    if (def->parent_name == def2->name) parent_defined = true;
                }
                if (!parent_defined)
                    throwError("class " + def->name + " extends undefined class " + def->parent_name);
            }
        }
    }

    void checkMain() {
        bool defined = false;
        for (auto def: defined_functions) {
            if (def->name == "main") {
                if (!def->args.empty())
                    throwError("main function mustn't take arguments");
                if (def->return_type->name != "int" || !def->return_type->is_not_array())
                    throwError("main function must return int");

                defined = true;
            }
        }
        if (!defined)
            throwError("main function not defined");
    }

public:
    explicit TypeChecker(Program *program) : program(program) {
        std::vector < CVar * > printIntArgs;
        printIntArgs.push_back(new CVar("arg", new CType("int", false)));
        defined_functions.push_back(new CFun(
                std::string("printInt"),
                new CType("void", false),
                printIntArgs));

        std::vector < CVar * > printStringArgs;
        printStringArgs.push_back(new CVar("arg", new CType("string", false)));
        defined_functions.push_back(new CFun(
                "printString",
                new CType("void", false),
                printStringArgs));

        defined_functions.push_back(new CFun(
                "error",
                new CType("void", false),
                std::vector<CVar *>()));

        defined_functions.push_back(new CFun(
                "readInt",
                new CType("int", false),
                std::vector<CVar *>()));

        defined_functions.push_back(new CFun(
                "readString",
                new CType("string", false),
                std::vector<CVar *>()));
    }

    void checkCorrectness() {
        auto classDefOnlyNameVisitor = new Class_Def_Name_Only_Visitor(defined_classes, class_defs, class_extend_defs);
        program->accept(classDefOnlyNameVisitor);
        checkNoIllegalExtend();

        auto functionDefVisitor = new Function_Def_Visitor(defined_functions, defined_classes, nullptr, nullptr);
        program->accept(functionDefVisitor); // check duplicates (function names and arg names)
        checkMain();

        auto classDefVisitor = new Class_Def_Visitor(defined_functions, defined_classes, defined_class_idents);
        for (auto def: class_defs) {
            def->accept(classDefVisitor);
        }
        int visited_class_extends_defs = 0;
        while (visited_class_extends_defs < class_extend_defs.size()) { // A extends B
            for (int i = 0; i < class_extend_defs.size(); i++) {
                auto def = class_extend_defs.at(i);
                if (defined_class_idents.find(def->ident_1) == defined_class_idents.end()
                    && defined_class_idents.find(def->ident_2) !=
                       defined_class_idents.end()) { // A isn't defined yet but B is
                    def->accept(classDefVisitor);
                    visited_class_extends_defs++;
                }
            }
        }

        defined_class_idents.clear();
        auto classDefInitVisitor = new Class_Def_Init_Visitor(defined_functions, defined_classes, defined_class_idents);
        for (auto def: class_defs) {
            def->accept(classDefInitVisitor);
        }
        visited_class_extends_defs = 0;
        while (visited_class_extends_defs < class_extend_defs.size()) { // A extends B
            for (int i = 0; i < class_extend_defs.size(); i++) {
                auto def = class_extend_defs.at(i);
                if (defined_class_idents.find(def->ident_1) == defined_class_idents.end()
                    && defined_class_idents.find(def->ident_2) !=
                       defined_class_idents.end()) { // A isn't defined yet but B is
                    def->accept(classDefInitVisitor);
                    visited_class_extends_defs++;
                }
            }
        }

        auto function_body_visitor = new Function_Body_Visitor(defined_functions, defined_classes);
        program->accept(function_body_visitor);

        delete (classDefOnlyNameVisitor);
        delete (functionDefVisitor);
        delete (classDefVisitor);
        delete (classDefInitVisitor);
        delete (function_body_visitor);
    }
};