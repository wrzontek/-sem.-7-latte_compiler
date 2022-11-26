#include <string>
#include <set>
#include <vector>
#include "Absyn.H"
#include "Skeleton.C"
#include "Common.cpp"
#include "FunctionDefVisitor.cpp"
#include "ClassDefNameOnlyVisitor.cpp"
#include "TypeVisitor.cpp"

class Class_Def_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_functions;
    std::vector<CClass *> &defined_classes;

    std::vector<CVar *> current_class_attributes;
    std::vector<CFun *> current_class_methods;

    Ident current_arg_name;
    CType *current_type = nullptr;

    explicit Class_Def_Visitor(std::vector<CFun *> &defined_functions, std::vector<CClass *> &defined_classes,
                               Type_Visitor *typeVisitor)
            : defined_functions(defined_functions), defined_classes(defined_classes), typeVisitor(typeVisitor) {
    }

    void visitFnDef(FnDef *fn_def) override {}; // dont visit global functions

    // todo do metod można odgrzać FunctionDefVisitor'a
    void visitClassDef(ClassDef *class_def) override {
        CClass *cclass = nullptr;
        for (auto def: defined_classes) {
            if (def->name == class_def->ident_) {
                cclass = def;
                break;
            }
        }
        if (cclass == nullptr) { exit(1); /*should never happen */}

        cclass->visited = true;
        current_class_attributes = std::vector<CVar *>();
        current_class_methods = std::vector<CFun *>();

        class_def->listclassmember_->accept(this);

        cclass->attributes = current_class_attributes;
        cclass->methods = current_class_methods;
    };

    void visitAttrMember(AttrMember *attr_member) override {
        current_type = typeVisitor->getType(attr_member->type_);
        attr_member->listitem_->accept(this);
    }

    void checkAttrRedefinition(Ident name, int line_number, int char_number) {
        for (auto attribute: current_class_attributes) {
            if (attribute->name == name) {
                throwError(line_number, char_number, "redefinition of attribute");
            }
        }
    }

    void visitNoInit(NoInit *no_init) override {
        checkAttrRedefinition(no_init->ident_, no_init->line_number, no_init->char_number);
        current_class_attributes.push_back(new CVar(no_init->ident_, current_type));
    }

    void visitInit(Init *init) override {
        checkAttrRedefinition(init->ident_, init->line_number, init->char_number);
        if (*current_type != *(typeVisitor->getExprType(init->expr_))) {
            throwError(init->line_number, init->char_number,
                       "initialization expression of different type than declared");
        }

        current_class_attributes.push_back(new CVar(init->ident_, current_type));
    }

    void visitClassExtendDef(ClassExtendDef *class_def) override {};

};

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

        auto typeVisitor = new Type_Visitor(defined_classes);

        auto functionDefVisitor = new Function_Def_Visitor(defined_functions, defined_classes, typeVisitor);
        program->accept(functionDefVisitor); // check duplicates (function names and arg names)
        checkMain();

        auto classDefVisitor = new Class_Def_Visitor(defined_functions, defined_classes, typeVisitor);
        for (auto def: class_defs) {
            def->accept(classDefVisitor);
        }
        program->accept(classDefVisitor); //check duplicates (member names)

    }
};