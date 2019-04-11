/**
    reflect.c
    円が右端まで行って戻ってくる
**/
#include <stdio.h>
#include <handy.h>

#define WINDOWSIZE 400
#define RADIUS 50

int main() {
    int x=0;  // 中心のx座標
    int y=0;
    int xv;  // x方向の速度[ピクセル/フレーム]
    int yv;

    HgOpen(WINDOWSIZE, WINDOWSIZE);

    xv = 5;
    yv = 3;
    while(1){
        if(x >= 0) x+=xv;
        if(y >= 0) y+=yv;
        HgClear();
        HgCircle(x, y, RADIUS);
        printf("%d %d\n",x,y);
        HgSleep(0.05);
        if (x >= WINDOWSIZE)  xv = -5;
        if (x <= 0)           xv = 5;
        if (y >= WINDOWSIZE)  yv = -3;
        if (y <= 0)           yv = 3;
    }

    HgGetChar();
    HgClose();
    return 0;
}
