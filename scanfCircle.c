#include<stdio.h>
#include<handy.h>

int main(){
  int inputNum1;
  int inputNum2;
  int inputNum3;

  printf("x軸座標：");
  scanf("%d",&inputNum1);
  printf("y軸座標：");
  scanf("%d",&inputNum2);
  printf("半径：");
  scanf("%d",&inputNum3);

  HgOpen(400,400);

  HgCircle(inputNum1,inputNum2,inputNum3);

  HgGetChar();
  HgClose();

  return 0;
}
