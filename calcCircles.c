/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 400;     //Open時の横幅
  int height = 400;　  //Open時の縦幅

  int Circle_y = 210;  //大きい円のy軸
  int Circle_x = 240;  //大きい円のx軸
  int radius = 120;    //大きい円の半径




  HgOpen(width,height);

  HgCircleFill(Circle_x,Circle_y,radius,1);
  HgCircleFill(Circle_x/6+(width-Circle_x),Circle_y,Circle_x/3,1);  //左の円
  HgCircleFill(Circle_x/3*2+(width-Circle_x),Circle_y,Circle_x/6,1);//右の円



  HgGetChar();
  HgClose();
  return 0;
}
