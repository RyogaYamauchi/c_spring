/*
  854003 山内龍我
*/

#include<stdio.h>

int main(){
  int inputNum1;  //入力用変数１
  int inputNum2;  //入力用変数２

  int add;  //たしざん
  int sub;  //引き算
  int mul;  //掛け算
  int waru; //わりざん

  printf("Input first number : ");
  scanf("%d",&inputNum1);
  printf("Input second number: ");
  scanf("%d",&inputNum2);

  add = inputNum1 + inputNum2;  //足し算の計算
  sub = inputNum1 - inputNum2;  //引き算の計算
  mul = inputNum1 * inputNum2;  //掛け算の計算
  waru = inputNum1 / inputNum2; //割り算の計算


  printf("%d + %d = %d\n",inputNum1,inputNum2,add);
  printf("%d - %d = %d\n",inputNum1,inputNum2,sub);
  printf("%d * %d = %d\n",inputNum1,inputNum2,mul);
  printf("%d / %d = %d\n",inputNum1,inputNum2,waru);


  return 0;
}
