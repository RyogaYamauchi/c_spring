/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 480;     //Open時の横幅
  int height = 480;    //Open時の縦幅

  int num ;
  int i;
  int j;

  int Circle_y = 0;  //大きい円のy軸
  int Circle_x = 0;  //大きい円のx軸
  int radius;    //大きい円の半径

  printf("input number : ");
  scanf("%d",&num);

  radius = width / num/2;        //円の半径
  Circle_x = Circle_x - radius;  //x軸状に動くための変数

  HgOpen(width, height);

  for(i=1;i<=num;i++){     //先にy軸状にかき、右にずれ、またy軸状にかく
    Circle_x = Circle_x + (radius*2);
    Circle_y = (radius*2);
    if(i%2==0){
      HgSetFillColor(HG_BLACK);
    }
    else{
      HgSetFillColor(HG_WHITE);
    }

    for(j=1;j<=num;j++){
       HgCircleFill(Circle_x,Circle_y*j-radius,radius,1);
    }
  }

  HgGetChar();
  HgClose();
  return 0;
}
