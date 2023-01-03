#include <iostream>
#include <stdlib.h>
#include <string.h>

extern "C" {
void printInt(int n) {
    std::cout << n << std::endl;
}

void printString(char *s) {
    std::cout << std::string(s) << std::endl;
}

void error() {
    std::cerr << "runtime error" << std::endl;
    exit(1);
}

int readInt() {
    int n;
    if (!(std::cin >> n)) {
        error();
    }
    return n;
}

char *readString() {
    std::string s;
    if (!std::getline(std::cin, s)) {
        error();
    }
    char *result = new char[s.length() + 1];
    strcpy(result, s.c_str());
    return result;
}

char *stringsConcat(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = (char *) malloc(len1 + len2 + 1);
    if (!result) {
        error();
    }
    strcpy(result, s1);
    strcpy(result + len1, s2);
    return result;
}

int stringsEqual(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int stringsNotEqual(const char *s1, const char *s2) {
    return !stringsEqual(s1, s2);
}
}