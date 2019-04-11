/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

#define WindowSize 400

int main(){

  int i;
  int v=0;  //初速度

  int Circle_y = 400;  //大きい円のy軸
  int Circle_x = 200;  //大きい円のx軸
  int radius = 50;    //大きい円の半径

  HgOpen(WindowSize, WindowSize);

  for(i=v;i>-100;i-=2){
    HgClear();
    HgCircleFill(Circle_x,Circle_y,radius,1);
    HgSleep(0.05);

    Circle_y = i + Circle_y;

  }

  HgGetChar();
  HgClose();
  return 0;
}
