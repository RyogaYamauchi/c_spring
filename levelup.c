/*****
    levelup.c
    レベルアップ時のメッセージを表示する
    Yamauchi Ryoga
*****/
#include <stdio.h>

int main() {
    int level;  // 現在のレベル
    int hp;  // 体力の増加値

    level = 12;  // レベル12になったとする
    hp = 34;  // 体力は34増える

        printf("トンヌラはレベル%dになった! 体力が%d上がった!",level,hp);

    return 0;
}
