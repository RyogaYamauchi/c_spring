#include<stdio.h>

int main(){
  int inputNum1;
  int inputNum2;
  int inputNum3;

  int sum;
  int mul;


  printf("一つ目の数字を入力してください：");
  scanf("%d",&inputNum1);
  printf("二つ目の数字を入力してください：");
  scanf("%d",&inputNum2);
  printf("三つ目の数字を入力してください：");
  scanf("%d",&inputNum3);

  sum = inputNum1 + inputNum2;
  mul = sum * inputNum3;

  printf("answer = %d\n",mul);

  return 0;
}
