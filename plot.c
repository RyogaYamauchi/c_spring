/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 600;     //Open時の横幅
  int height = 400;    //Open時の縦幅

  int segment = 30;

  int i;
  int y;



  HgOpen(width,height);

  for(i=0;i<=600;i++){
    if(i % 10 == 0){
      y = i/2+30;
      HgCircleFill(i,y,1,1);
    }
  }

  HgGetChar();
  HgClose();
  return 0;
}
