#include<stdio.h>

int main(){
  int num;
  int ave = 0;
  int sum = 0;
  int cnt = 0;

  while(1){
    scanf("%d",&num);
    if(num==0) break;
    sum = sum + num;
    cnt++;
  }
  ave = sum/cnt;
  printf("平均は%d\n",ave);
}
