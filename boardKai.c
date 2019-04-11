/*****
      boardKai.c
      9x9のゲーム盤にランダムに20個のコマを配置し、
      縦か横に4つ並んでいるか判定する
*****/

#include <stdio.h>
#include <stdlib.h>  // rand関数を使うために必要
#include <time.h>  // time関数を使うために必要

int main() {
    int board[9][9] = {};  // 盤、0は駒無し、1は駒あり、初期状態はすべて0
    /*
	   配列に初期値を代入する際に{}の中に何も書かなければ
	   すべての要素に0を代入することができる
	*/

    int x, y;  // コマを配置する座標
    int koma;  // 配置するコマの個数を数えるカウンタ変数
    int i, j;  // カウンタ変数


    srand(time(NULL));  // 乱数を現在時刻で初期化する

    // 20個のコマをランダムな座標に配置する
    koma = 0;
    do {
        x = rand() % 9;  // xの値を0〜8の乱数値とする
        y = rand() % 9;  // yの値を0〜8の乱数値とする
        if (board[x][y] == 0) {  // (x,y)の位置にコマがなければ
            board[x][y] = 1;  // コマ有りにする
            koma++;  // 置いたコマの個数を1増やす
        }
    } while (koma < 20);  // 20個コマを置くまで繰り返す

    // 盤の表示
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");  // 1行分表示したら改行する
    }

    // 判定する
    // xの判定
    for(i=0;i<9;i++){  //y
      for(j=0;j<6;j++){  //x
        if(board[i][j]==1 && board[i][j+1]==1 && board[i][j+2]==1 && board[i][j+3]==1){
          printf("横に揃いました!\n");
          printf("{%d,%d %d,%d %d,%d %d,%d}\n",i,j,i,j+1,i,j+2,i,j+3);
        }
      }
    }
    //yの判定
    for(i=0;i<9;i++){  //x
      for(j=0;j<6;j++){  //y
        if(board[j][i]==1 && board[j+1][i]==1 && board[j+2][i]==1 && board[j+3][i]==1){
          printf("縦に揃いました\n");
          printf("{%d,%d %d,%d %d,%d %d,%d}\n",i,j,i+1,j,i+2,j,i+3,j);
        }
      }
    }

    //斜めの判定
    for(i=0;i<6;i++){  //y
      for(j=3;j<9;j++){  //x
        if(board[j][i]==1 && board[j+1][i+1]==1 && board[j+2][i+2]==1 && board[j+3][i+3]==1){
          printf("斜めに揃いました\n");
        }
     }
    }
    for(i=3;i<9;i++){  //y
      for(j=3;j<9;j++){  //x
        if(board[j][i]==1 && board[j+1][i-1]==1 && board[j+2][i-2]==1 && board[j+3][i-3]==1){
          printf("斜めに揃いました\n");
        }
      }
    }
    return 0;
}
