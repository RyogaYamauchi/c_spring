/*
  854003 山内龍我
*/


#include<stdio.h>
#include<handy.h>

int main(){

  int width = 400;//Open時の横幅
  int height = 400;//Open時の縦幅

  int numX;  //入力用変数（座標x)
  int numY;  //入力用変数（座標系y）
  int radius;  //入力用変数（半径）

  double range = 0;  //二つの円の中心の距離

  printf("円の座標を半径を入力してください\n座標 x ：");
  scanf("%d",&numX);
  printf("座標 y ：");
  scanf("%d",&numY);
  printf("半径 ：");
  scanf("%d",&radius);

  range = ((numX - 200)*(numX - 200)) + ((numY - 200)*(numY - 200));  //二つの円の中心の座標の距離

  printf("%d and %d\n",(numX-200),(numY - 200));

  HgOpen(width,height);
  HgSetFillColor(HG_BLUE);

  HgCircle(200,200,150);  //中心の円

  //1792
  //二つの円の中心の座標の距離が二つの円の半径の和より小さい時重なっていると判定する
  if( range < ((150 + radius)*(150 + radius))){
      HgSetFillColor(HG_RED);//重なっている時だけ青にする
  }

  HgCircleFill(numX,numY,radius,1);

  printf("%f",range);

  HgGetChar();
  HgClose();
  return 0;
}
