#include<stdio.h>

int main(){
  int score[10] = {66, 98, 56, 48, 73, 35, 87, 60, 52, 65};
  int i;
  int num;
  int cnt = 0;

  printf("合格点を入力してください");
  scanf("%d",&num);

  for(i=0;i<10;i++){
    if(score[i]>=num){
      cnt++;
    }
  }
  printf("合格者数は%dです\n",cnt);

  return 0;
}
