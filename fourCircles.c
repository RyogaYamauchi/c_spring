/**
    854003 Yamauchi Ryoga
**/

#include<stdio.h>
#include<handy.h>

int main(){
  HgOpen(600, 400);
    HgSetFillColor(HG_RED);
  HgCircleFill(120, 120, 120, 1);
    HgSetFillColor(HG_BLUE);
  HgCircleFill(120, 280, 120, 1);
    HgSetFillColor(HG_GREEN);
  HgCircleFill(280, 280, 120, 1);
  HgSetFillColor(HG_YELLOW);
  HgCircleFill(280, 120, 120, 1);

      HgGetChar();
      HgClose();
      return 0;
}
