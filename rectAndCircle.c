#include<stdio.h>
#include<handy.h>

int main(){
  int width = 600;    //Open時の横幅
  int height = 400;　  //Open時の縦幅

  // Circle option
  int x = width/2;
  int y = height/2;
  int radius = 150;

  HgOpen(width,height);

  HgSetFillColor(HG_BLUE);
  HgBoxFill(150, 50, 300, 300, 1);

  HgSetFillColor(HG_YELLOW);
  HgCircleFill(x,y,radius, 1);

  HgGetChar();
  HgClose();
  return 0;
}
