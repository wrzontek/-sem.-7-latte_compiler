#pragma once

#include <iostream>
#include <set>
#include <vector>

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
    explicit CType(Ident name, std::vector<int> array_dims) : name(name), array_dims(array_dims) {}

    Ident name; // void, int, bool, string, <class>
    std::vector<int> array_dims; // empty if type is not array
};

inline bool operator==(const CType &lhs, const CType &rhs) {
    return lhs.name == rhs.name && lhs.array_dims == rhs.array_dims;
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
    explicit CClass(Ident name, Ident parent, std::vector<CVar *> attributes, std::vector<CFun *> methods)
            : name(name),
              parent(parent),
              attributes(attributes),
              methods(methods) {}

    bool visited = false; // for ordering visits, parents then children

    Ident name;
    Ident parent;
    std::vector<CVar *> attributes;
    std::vector<CFun *> methods;
};