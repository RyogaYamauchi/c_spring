#include<stdio.h>

int main(){
  int num;
  int sum = 0;
  while(1){
    scanf("%d",&num);
    sum = sum + num;
    if(num==0) break;
  }
  printf("合計は%d\n",sum);
}
