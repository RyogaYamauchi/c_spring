/**
    handy.c
    2018.5.9 Yamauchi Ryoga
**/

#include <stdio.h>
#include <handy.h>

int main() {
    HgOpen(600, 400);
    HgCircle(300, 150, 120);
    HgGetChar();
    HgClose();
    return 0;
}
