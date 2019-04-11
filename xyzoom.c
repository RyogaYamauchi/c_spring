/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

#define WindowSize 400

int main(){

  int num ;
  int i;

  int Circle_y = 0;  //大きい円のy軸
  int Circle_x = 0;  //大きい円のx軸
  int radius = 50;    //大きい円の半径

  HgOpen(WindowSize, WindowSize);

  while(1){
    HgClear();
    HgCircleFill(Circle_x,Circle_y,radius,1);
    HgSleep(0.05);
    Circle_x = Circle_x+5;
    Circle_y = Circle_y+5;
    if(Circle_x > 400 && Circle_y > 400) break;
  }

  HgGetChar();
  HgClose();
  return 0;
}
