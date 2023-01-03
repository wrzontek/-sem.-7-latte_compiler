//gcc -o foo.s -S foo.c

#include <stdio.h>

void printString(char *s) {
    puts(s);
}

int main() {
    int a = 123;
    printString("baba\n");
    printString("chop\n");
    return a;
}

int f(int b) {
    printString("dziecko\n");
    return b;
}