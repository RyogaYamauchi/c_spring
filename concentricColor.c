/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 600;     //Open時の横幅
  int height = 600;    //Open時の縦幅

  int Circle_x = 300;  //円のx軸
  int Circle_y = 300;  //円のy軸
  int radius;    //半径

  int small = 50;     //小さい円の半径
  int large = 250;    //大きい円の半径
  int i;
  int cnt = 1;




  HgOpen(width,height);
  HgSetColor(HG_BLUE);

  for(i=small;i<=large;i++){
    if(i % 50 == 0) {
      if(cnt % 2 == 0){
        HgSetColor(HG_RED);
      }
      else{
        HgSetColor(HG_BLUE);
      }
      cnt++;
      radius = i;
      HgCircle(Circle_x,Circle_y,radius);
    }
  }

  HgGetChar();
  HgClose();
  return 0;
}
