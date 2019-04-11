/* 854003 山内龍我 */

#include<stdio.h>

int main(){
  int array[100];   //要素の配列
  int num;          //データの個数入力用変数
  int i;            //ループ用変数
  int sum = 0;;     //足し込み

  printf("データの個数を入力してください");
  scanf("%d",&num);

  //各配列に要素を入力
  for(i=0;i<num;i++){
    printf("input number %d :",i);
    scanf("%d",&array[i]);
    if(sum < array[i]) sum = array[i];
  }

  printf("最大値は%dです\n",sum);


  return 0;
}
