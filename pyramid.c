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

  radius = width / num/2;  Circle_x = Circle_x - radius;


  HgOpen(width, height);

  Circle_x = Circle_x;

  for(i=num;i>=1;i--){
    Circle_x = Circle_x + (radius*2);
    Circle_y = (radius*2);
    for(j=i;j>=1;j--){
       HgCircle(Circle_x,Circle_y*j-radius,radius);
    }
  }

  HgGetChar();
  HgClose();
  return 0;
}
