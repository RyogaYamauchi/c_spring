/*
  854003　山内龍我
*/
#include<stdio.h>

int main(){
  int num1;  //入力用変数　手持ちの金額
  int num2;  //入力用変数　商品の単価
  int num3;  //入力用変数　買いたい個数

  int back = 0; //お釣り
  int count = 0;  //買える個数

  printf("手持ちの金額、商品の金額、買いたい個数を入力してください\n");
  printf("手持ちの金額：");
  scanf("%d",&num1);
  printf("商品の単価　：");
  scanf("%d",&num2);
  printf("買いたい個数：");
  scanf("%d",&num3);

  back = num1-(num2*num3);  //お釣りの計算
  count = num1/num2;        //買える個数の計算


  if(back >= 0){       //お釣りがある場合
    printf("買える。お釣りは%d円\n",back);
  }
  else{                //お釣りがない場合
    printf("買えない。%d個までなら買える\n",count);
  }


  return 0;
}
