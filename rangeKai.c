#include<stdio.h>

int main(){
  int num;
  int num2;
  int enter;

  printf("判定値：");
  scanf("%d",&num);


  printf("判定値：");
  scanf("%d",&num2);

  while(1){
    printf("判定値：");
    scanf("%d",&enter);
    if(num< num2){
      if(num > enter || num2< enter) break;
    }
    else{
      if(num2 > enter || num < enter) break;
    }
  }
  return 0;
}
