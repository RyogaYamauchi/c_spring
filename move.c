/*****
    move.c
    円を動かしてみる
    M.Minakuchi
*****/
#include <stdio.h>
#include <handy.h>

#define WINDOWSIZE 400
#define RADIUS 50

int main() {
    int x;  // 中心のx座標

    HgOpen(WINDOWSIZE, WINDOWSIZE);

    for (x = 0; x < WINDOWSIZE; x += 5) {  // 移動速度を5に増やしてみる
        HgClear();  // ウィンドウを消去する
        HgCircle(x, WINDOWSIZE / 2, RADIUS);
        HgSleep(0.05);  // 0.05秒間実行を止める
    }

    HgGetChar();
    HgClose();
    return 0;
}
