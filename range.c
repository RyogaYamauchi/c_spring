#include<stdio.h>

int main(){
  int sma;
  int lar;
  int num;

  printf("最小値：");
  scanf("%d",&sma);
  
  printf("最大値：");
  scanf("%d",&lar);

  while(1){
    printf("判定値：");
    scanf("%d",&num);
    if( num<sma || num>lar) break;
  }
  return 0;
}
