/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 600;     //Open時の横幅
  int height = 400;    //Open時の縦幅

  int num ;
  int i;

  int Circle_y;  //大きい円のy軸
  int Circle_x ;  //大きい円のx軸
  int radius = 50;    //大きい円の半径

  printf("input number x :");
  scanf("%d",&Circle_x);
  printf("input number y :");
  scanf("%d",&Circle_y);



  HgOpen(width, height);

  HgBox(150,100,300,200);

  if(Circle_x < 150 || Circle_x > 450 || Circle_y < 100 || Circle_y > 300){  //青になる範囲
    HgSetFillColor(HG_BLUE);
  }
  else{     //それ以外の赤になる範囲
    HgSetFillColor(HG_RED);
  }
  HgCircleFill(Circle_x,Circle_y,radius,1);

  HgGetChar();
  HgClose();
  return 0;
}
