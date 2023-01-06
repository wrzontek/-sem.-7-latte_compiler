#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printInt(int n) {
    printf("%d\n", n);
}

void printString(const char *s) {
    printf("%s\n", s);
}

void error() {
    fprintf(stderr, "runtime error\n");
    exit(1);
}

int readInt() {
    char *s = NULL;
    size_t size = 0;
    if (getline(&s, &size, stdin) == -1) {
        error();
    }
    int result = atoi(s);
    free(s);
    return result;
}

char *readString() {
    char *s = NULL;
    size_t size = 0;
    if (getline(&s, &size, stdin) == -1) {
        error();
    }
    size_t len = strlen(s);
    if (s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
    char *result = malloc(len + 1);
    if (!result) {
        error();
    }
    strcpy(result, s);
    free(s);
    return result;
}

char *_stringsConcat(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result) {
        error();
    }
    strcpy(result, s1);
    strcpy(result + len1, s2);
    return result;
}

int _stringsEqual(const char *s1, const char *s2) {
    if (strcmp(s1, s2) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int _stringsNotEqual(const char *s1, const char *s2) {
    return !_stringsEqual(s1, s2);
}
