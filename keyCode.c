/*****
    keycode.c
    押したキーの値を表示する
    M.Minakuchi
*****/
#include <stdio.h>
#include <handy.h>

int main() {
    int key;  // 押したキーの値を覚えておく変数

    HgOpen(400, 400);
    for (;;) {
        key = HgGetChar();
        printf("key = %d\n", key);
        if (key == ' ')  break;  // スペースが押されたらループを抜ける
    }

    HgClose();
    return 0;
}
