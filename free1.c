/**
    reflect.c
    円が右端まで行って戻ってくる
**/
#include <stdio.h>
#include <handy.h>
#include <math.h>
#include <stdbool.h>

#define WINDOWSIZE 800
#define RADIUS 50
#define Width 20

//グローバル変数定義
float a = -1;  //重力加速度
float g = 1; //重力加速度
float weight = 1; //質量
float e = 0.5; //反発係数
float Height = 600;

int main() {
  //ローカル変数定義(main)
    int x=200;  // 中心のx座標
    float y=600;  //中心のy座標
    float xv = 0;  //x方向の初速度
    float yv = 2;  //y方向の初速度
    int cnt = -1;
    int h_1;  //高さ
    int h_2;  //反発後の高さ

    bool Fall = true;

    HgOpen(WINDOWSIZE, WINDOWSIZE);

    while(1){
      cnt++;
      if(Fall == true){       //自由落下
        yv = yv + (g * cnt);             //yの加速度
        y = Height - ( yv * weight );    //yの位置

        if(y<=0) {
          cnt = 0;
          Fall = false;
          printf("鉛直投げ上げに切り替え\n");
        }
      }
      else{                   //鉛直投げ上げ
        yv = (yv - (g * cnt) *e);     //yの加速度
        y = (yv/25  * cnt) ;//- (( g * cnt * cnt)/2) ;        //yの位置
        if(yv<=0) {
          cnt=0;
          Fall = true;
          yv = 0;
          Height = Height*0.9;
          printf("自由落下に切り替え\n");
        }
      }

      HgClear();
      HgCircle(x, y, RADIUS);
      printf("x:%d xv:%f y:%f yv:%f cnt:%d\n",x,xv,y,yv,cnt);    //Debug
      HgSleep(0.05);
    }

    HgGetChar();
    HgClose();
    return 0;
}
