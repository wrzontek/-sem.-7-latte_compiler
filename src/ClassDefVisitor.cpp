#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"
#include "FunctionDefVisitor.cpp"

class Class_Def_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_functions; // global + class methods
    std::vector<CClass *> &defined_classes;
    std::set <Ident> &defined_class_idents;
    std::set <Ident> already_redefined_attributes;
    std::set <Ident> already_redefined_methods;


    CClass *current_class = nullptr;
    CType *current_type = nullptr;

    explicit Class_Def_Visitor(std::vector<CFun *> &defined_functions, std::vector<CClass *> &defined_classes,
                               std::set <Ident> &defined_class_idents)
            : defined_functions(defined_functions), defined_classes(defined_classes),
              defined_class_idents(defined_class_idents) {
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
        if (current_class == nullptr) { myExit(11); /*should never happen */}

        // adding "self" attribute of type <class>
        current_class->attributes.push_back(new CVar(
                "self",
                new CType(current_class->name, false)));
        class_def->listclassmember_->accept(this);

        defined_class_idents.insert(current_class->name);
    };

    void visitClassExtendDef(ClassExtendDef *class_def) override {
        current_class = nullptr;
        for (auto def: defined_classes) {
            if (def->name == class_def->ident_1) {
                current_class = def;
                break;
            }
        }
        if (current_class == nullptr) { myExit(12); /*should never happen */}

        for (auto def: defined_classes) {
            if (def->name == class_def->ident_2) {
                current_class->parent = def;
                break;
            }
        }
        if (current_class->parent == nullptr) { myExit(13); /*should never happen */}

        // adding "self" attribute of type <class>
        current_class->attributes.push_back(new CVar(
                "self",
                new CType(current_class->name, false)));

        already_redefined_attributes.clear();
        already_redefined_methods.clear();

        for (auto met: current_class->parent->methods) { current_class->methods.push_back(met); }
        for (auto attr: current_class->parent->attributes) {
            if (attr->name != "self") current_class->attributes.push_back(attr);
        }

        class_def->listclassmember_->accept(this);

        defined_class_idents.insert(current_class->name);
    };

    ////////////////////////////////

    void visitAttrMember(AttrMember *attr_member) override {
        typeVisitor = new Type_Visitor(defined_classes, current_class->attributes, defined_functions);

        current_type = typeVisitor->getType(attr_member->type_);
        delete (typeVisitor);
        if (current_type->name == "void")
            throwError(attr_member->line_number, attr_member->char_number,
                       "cannot declare void type attribute");

        attr_member->listitem_->accept(this);
    }

    void defineOrRedefineAttr(Ident name, int line_number, int char_number) {
        for (int i = 0; i < current_class->attributes.size(); i++) {
            auto attribute = current_class->attributes.at(i);
            if (attribute->name == name) {
                if (current_class->parent == nullptr)
                    throwError(line_number, char_number, "redefinition of attribute");

                bool ok = false;
                for (auto parent_attribute: current_class->parent->attributes) {
                    if (parent_attribute->name == name &&
                        already_redefined_attributes.find(name) == already_redefined_attributes.end()) {
                        already_redefined_attributes.insert(name);
                        current_class->attributes.erase(current_class->attributes.begin() + i);
                        ok = true;
                        break;
                    }
                }

                if (ok) break;

                throwError(line_number, char_number, "redefinition of attribute");
            }
        }

        current_class->attributes.push_back(new CVar(name, current_type));
    }

    void visitNoInit(NoInit *no_init) override {
        defineOrRedefineAttr(no_init->ident_, no_init->line_number, no_init->char_number);
    }

    void visitInit(Init *init) override {
        defineOrRedefineAttr(init->ident_, init->line_number, init->char_number);
    }

    ////////////////////////////////

    void visitMethodMember(MethodMember *method_member) override {
        auto method_def_visitor = new Function_Def_Visitor(current_class->methods, defined_classes,
                                                           current_class->parent,
                                                           &already_redefined_methods);
        method_member->accept(method_def_visitor);
        current_class->methods = method_def_visitor->defined_functions;
    }

};

class Class_Def_Init_Visitor : public Skeleton {
public:
    Type_Visitor *typeVisitor;

    std::vector<CFun *> &defined_functions;
    std::vector<CClass *> &defined_classes;
    std::set <Ident> &defined_class_idents;

    CClass *current_class = nullptr;
    CType *current_type = nullptr;

    explicit Class_Def_Init_Visitor(std::vector<CFun *> &defined_functions,
                                    std::vector<CClass *> &defined_classes,
                                    std::set <Ident> &defined_class_idents)
            : defined_functions(defined_functions), defined_classes(defined_classes),
              defined_class_idents(defined_class_idents) {
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
        if (current_class == nullptr) { myExit(14); /*should never happen */}
        // adding "self" attribute of type <class>
        current_class->attributes.push_back(new CVar(
                "self",
                new CType(current_class->name, false)));

        class_def->listclassmember_->accept(this);

        defined_class_idents.insert(current_class->name);
    };

    void visitClassExtendDef(ClassExtendDef *class_def) override {
        current_class = nullptr;
        for (auto def: defined_classes) {
            if (def->name == class_def->ident_1) {
                current_class = def;
                break;
            }
        }
        if (current_class == nullptr) { myExit(15); /*should never happen */}

        class_def->listclassmember_->accept(this);

        defined_class_idents.insert(current_class->name);
    };

    void visitMethodMember(MethodMember *method_member) override {}; // don't visit

    ////////////////////////////////

    void visitAttrMember(AttrMember *attr_member) override {
        typeVisitor = new Type_Visitor(defined_classes, current_class->attributes, defined_functions);
        current_type = typeVisitor->getType(attr_member->type_);
        delete (typeVisitor);
        attr_member->listitem_->accept(this);
    }

    void visitInit(Init *init) override {
        typeVisitor = new Type_Visitor(defined_classes, current_class->attributes, defined_functions);
        auto expr_type = typeVisitor->getExprType(init->expr_);

        if (current_type->is_array != expr_type->is_array ||
            (current_type->name != expr_type->name &&
             !isDescendantOf(current_type->name, expr_type->name, defined_classes))) {
            delete (typeVisitor);

            throwError(init->line_number, init->char_number,
                       "initialization expression of different type than declared");
        }
        delete (typeVisitor);
    }

};


