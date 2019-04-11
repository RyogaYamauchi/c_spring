/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

#define WindowSize 400

int main(){

  int num ;
  int i;

  int Circle_y = 210;  //大きい円のy軸
  int Circle_x = 240;  //大きい円のx軸
  int radius = 120;    //大きい円の半径

  HgOpen(WindowSize, WindowSize);

  HgCircleFill(numX,numY,radius,1);

  HgGetChar();
  HgClose();
  return 0;
}
