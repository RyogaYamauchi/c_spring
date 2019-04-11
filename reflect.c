/**
    reflect.c
    円が右端まで行って戻ってくる
**/
#include <stdio.h>
#include <handy.h>

#define WINDOWSIZE 400
#define RADIUS 50

int main() {
    int x;  // 中心のx座標
    int v;  // x方向の速度[ピクセル/フレーム]

    HgOpen(WINDOWSIZE, WINDOWSIZE);

    v = 5;
    while(1){
      for (x = 0; x >= 0; x += v) {
        HgClear();
        HgCircle(x, WINDOWSIZE / 2, RADIUS);
        HgSleep(0.05);
        if (x >= WINDOWSIZE) {
            v = -5;
        }
        if (x <= 0){
            v = 5;
        }
      }
    }


    HgGetChar();
    HgClose();
    return 0;
}
