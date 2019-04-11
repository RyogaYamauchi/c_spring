/****
    widthAndColor.c
    854003 Yamauchi Ryoga
*****/

#include <stdio.h>
#include <handy.h>

int main() {
    HgOpen(600, 400);
    HgSetColor(HG_RED);
    HgBox(10, 150, 100, 100);  // the left side square

    HgSetWidth(4);
    HgBox(130, 150, 100, 100);  // 2nd square
    HgSetColor(HG_BLUE);
    HgBox(250, 150, 100, 100);  // 3rd square

    HgSetWidth(1);
    HgBox(370, 150, 100, 100);  // 4th square
    HgSetColor(HG_BLACK);
    
    HgBox(490, 150, 100, 100);  // the right side square

    HgGetChar();
    HgClose();
    return 0;
}
