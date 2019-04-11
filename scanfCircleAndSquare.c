#include<stdio.h>
#include<handy.h>

int main(){
  int inputNum1;
  int inputNum2;
  int inputNum3;

  int Square_x;
  int Square_y;

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


    HgCircle(inputNum1,inputNum2,inputNum3);
    HgBox(Square_x,Square_y,inputNum3*2,inputNum3*2);

    HgGetChar();
    HgClose();

    return 0;
}
