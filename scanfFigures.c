/*
 854003 山内龍我
*/



#include<stdio.h>
#include<handy.h>

int main(){
  int inputNum1;   //入力用変数（円のx座標）
  int inputNum2;   //入力用変数（円のy座標）
  int inputNum3;   //入力用変数（円の半径）

  int Square_x;   //四角形のx座標
  int Square_y;   //四角形のy座標

    printf("x軸座標：");
    scanf("%d",&inputNum1);
    printf("y軸座標：");
    scanf("%d",&inputNum2);
    printf("半径：");
    scanf("%d",&inputNum3);

    Square_x = inputNum1 - inputNum3;
    Square_y = inputNum2 - inputNum3;

    printf("正方形の左下の座標は%d , %dです\n",Square_x,Square_y);

    HgOpen(400,400);


    HgCircle(inputNum1,inputNum2,inputNum3);      //円の描画
    HgBox(Square_x,Square_y,inputNum3*2,inputNum3*2);    //四角形の描画
    HgLine(Square_x,Square_y,Square_x+inputNum3*2,Square_y+inputNum3*2);    //対角線の描画
    HgLine(Square_x,Square_y+inputNum3*2,Square_x+inputNum3*2,Square_y);

    HgGetChar();
    HgClose();

    return 0;
}
