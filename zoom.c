/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

#define WindowSize 400

int main(){

  int num ;
  int i;

  int Circle_y = 200;  //大きい円のy軸
  int Circle_x = 200;  //大きい円のx軸
  int radius=0;    //大きい円の半径

  HgOpen(WindowSize, WindowSize);

  for(i=radius;i<300;i+=5){
    HgClear();
    HgCircleFill(Circle_x,Circle_y,i,1);
    HgSleep(0.05);
  }

  HgGetChar();
  HgClose();
  return 0;
}
