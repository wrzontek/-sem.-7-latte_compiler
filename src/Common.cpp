#pragma once

#include <iostream>
#include <vector>
#include "Absyn.H"

bool isBasicType(Ident type_name) {
    return type_name == "int" || type_name == "boolean" || type_name == "string" || type_name == "void";
}

bool isBuiltInFunction(Ident name) {
    return name == "printInt" || name == "printString" || name == "error" || name == "readInt" || name == "readString";
}

void throwError(int line_number, int char_number, std::string content) {
    std::cerr << "ERROR\n";
    std::cerr << std::to_string(line_number) + "," + std::to_string(char_number) + ": "
                 + content << std::endl;
    exit(1);
}

void throwError(std::string content) {
    std::cerr << "ERROR\n";
    std::cerr << content << std::endl;
    exit(1);
}

struct CType {
    explicit CType(Ident name, bool is_array) : name(name), is_array(is_array) {}

    Ident name; // void, int, bool, string, <class>
    bool is_array;

    bool is_not_array() {
        return !is_array;
    }
};

inline bool operator==(const CType &lhs, const CType &rhs) {
//    std::cout << lhs.name << " " << lhs.array_dims.size() << std::endl;
//    std::cout << rhs.name << " " << rhs.array_dims.size() << std::endl;

    return lhs.name == rhs.name && lhs.is_array == rhs.is_array;
}

inline bool operator!=(const CType &lhs, const CType &rhs) { return !(lhs == rhs); }


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
    explicit CClass(Ident name, Ident parent_name, CClass *parent, std::vector<CVar *> attributes,
                    std::vector<CFun *> methods)
            : name(name),
              parent_name(parent_name),
              parent(parent),
              attributes(attributes),
              methods(methods) {}

    Ident name;
    Ident parent_name;
    CClass *parent;
    std::vector<CVar *> attributes;
    std::vector<CFun *> methods;
};

void myExit(int a) {
//    std::cerr << "EXIT: " + std::to_string(a) << std::endl;
    exit(1);
}

bool isDescendantOf(Ident target_class, Ident potential_descendant, std::vector<CClass *> const &classes) {
    if (!isBasicType(potential_descendant)) {
        CClass *cclass = nullptr;
        for (auto def: classes) {
            if (def->name == potential_descendant) {
                cclass = def;
                break;
            }
        }
        if (cclass == nullptr) myExit(10);

        while (cclass->parent != nullptr) {
            if (cclass->parent->name == target_class)
                return true;
            cclass = cclass->parent;
        }
    }
    return false;
}