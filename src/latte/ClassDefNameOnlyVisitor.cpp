#pragma once

#include <string>
#include <set>
#include <vector>
#include "Common.cpp"

class Class_Def_Name_Only_Visitor : public Skeleton {
public:
    std::vector<CClass *> &defined_classes;
    std::vector<ClassDef *> &class_defs;
    std::vector<ClassExtendDef *> &class_extend_defs;

    explicit Class_Def_Name_Only_Visitor(std::vector<CClass *> &defined_classes,
                                         std::vector<ClassDef *> &class_defs,
                                         std::vector<ClassExtendDef *> &class_extend_defs)
            : defined_classes(defined_classes), class_defs(class_defs), class_extend_defs(class_extend_defs) {}

    void classVisit(Ident name, Ident parent_name, int line_number, int char_number) {
        if (name == parent_name) {
            throwError(line_number, char_number, "class tries to extend itself");
        }

        for (auto def: defined_classes) {
            if (def->name == name) {
                throwError(line_number, char_number, "redefinition of class " + name);
            }
        }

        defined_classes.push_back(new CClass(name, parent_name, nullptr, std::vector<CVar *>(), std::vector<CFun *>()));
    }

    void visitClassDef(ClassDef *class_def) override {
        class_defs.push_back(class_def);
        classVisit(class_def->ident_, "", class_def->line_number, class_def->char_number);
    };

    void visitClassExtendDef(ClassExtendDef *class_def) override {
        class_extend_defs.push_back(class_def);
        classVisit(class_def->ident_1, class_def->ident_2, class_def->line_number, class_def->char_number);
    };
};