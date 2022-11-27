#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"
#include "FunctionDefVisitor.cpp"

class Class_Def_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_global_functions;
    std::vector<CClass *> &defined_classes;

    CClass *current_class = nullptr;
    CType *current_type = nullptr;

    explicit Class_Def_Visitor(std::vector<CFun *> &defined_global_functions, std::vector<CClass *> &defined_classes)
            : defined_global_functions(defined_global_functions), defined_classes(defined_classes) {
    }

    void visitFnDef(FnDef *fn_def) override {}; // dont visit global functions

    void visitClassDef(ClassDef *class_def) override {
        current_class = nullptr;
        for (auto def: defined_classes) {
            if (def->name == class_def->ident_) {
                current_class = def;
                break;
            }
        }
        if (current_class == nullptr) { exit(1); /*should never happen */}

        class_def->listclassmember_->accept(this);

        current_class->visited = true;
    };

    void visitClassExtendDef(ClassExtendDef *class_def) override {};

    ////////////////////////////////

    void visitAttrMember(AttrMember *attr_member) override {
        typeVisitor = new Type_Visitor(defined_classes, current_class->attributes, defined_global_functions);

        current_type = typeVisitor->getType(attr_member->type_);
        delete (typeVisitor);
        attr_member->listitem_->accept(this);
    }

    void checkAttrRedefinition(Ident name, int line_number, int char_number) {
        for (auto attribute: current_class->attributes) {
            if (attribute->name == name) {
                throwError(line_number, char_number, "redefinition of attribute");
            }
        }
    }

    void visitNoInit(NoInit *no_init) override {
        checkAttrRedefinition(no_init->ident_, no_init->line_number, no_init->char_number);
        current_class->attributes.push_back(new CVar(no_init->ident_, current_type));
    }

    void visitInit(Init *init) override {
        checkAttrRedefinition(init->ident_, init->line_number, init->char_number);

        current_class->attributes.push_back(new CVar(init->ident_, current_type));
    }

    ////////////////////////////////

    void visitMethodMember(MethodMember *method_member) override {
        auto method_def_visitor = new Function_Def_Visitor(current_class->methods, defined_classes);
        method_member->accept(method_def_visitor);
        current_class->methods = method_def_visitor->defined_global_functions;
    }

};

class Class_Def_Init_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_global_functions;
    std::vector<CClass *> &defined_classes;

    CClass *current_class = nullptr;
    CType *current_type = nullptr;

    explicit Class_Def_Init_Visitor(std::vector<CFun *> &defined_global_functions,
                                    std::vector<CClass *> &defined_classes)
            : defined_global_functions(defined_global_functions), defined_classes(defined_classes) {
    }

    void visitFnDef(FnDef *fn_def) override {}; // dont visit global functions

    void visitClassDef(ClassDef *class_def) override {
        current_class = nullptr;
        for (auto def: defined_classes) {
            if (def->name == class_def->ident_) {
                current_class = def;
                break;
            }
        }
        if (current_class == nullptr) { exit(1); /*should never happen */}

        class_def->listclassmember_->accept(this);
    };

    void visitClassExtendDef(ClassExtendDef *class_def) override {};

    ////////////////////////////////

    void visitAttrMember(AttrMember *attr_member) override {
        typeVisitor = new Type_Visitor(defined_classes, current_class->attributes, defined_global_functions);
        current_type = typeVisitor->getType(attr_member->type_);
        delete (typeVisitor);
        attr_member->listitem_->accept(this);
    }

    void visitInit(Init *init) override {
        typeVisitor = new Type_Visitor(defined_classes, current_class->attributes, defined_global_functions);

        if (*current_type != *(typeVisitor->getExprType(init->expr_))) {
            delete (typeVisitor);
            throwError(init->line_number, init->char_number,
                       "initialization expression of different type than declared");
        }
        delete (typeVisitor);
    }
};


