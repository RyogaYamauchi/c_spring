/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 600;     //Open時の横幅
  int height = 600;    //Open時の縦幅

  int num ;
  int i;

  int x;
  int haba;

  printf("input number :");
  scanf("%d",&num);

  HgOpen(width,height);

  x = width / num;  //

  for(i=0;i<num;i++){
    HgLine(haba,0,haba,600);
    HgLine(0,haba,600,haba);
    haba = haba + x;

  }



  HgGetChar();
  HgClose();
  return 0;
}
