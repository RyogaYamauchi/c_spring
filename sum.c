#include<stdio.h>

int main(){
  int num =0;
  int count = 1;
  int goukei = 0;

  printf("inputNumber : ");
  scanf("%d",&num);

  if(num < 0){
    while(1){
      printf("inputNumber : ");
      scanf("%d",&num);
      if(num > 0){
        break;
      }
    }
  }

  while(count <= num){
    goukei = count + goukei;
    count++;
  }
  printf("%d\n",goukei);
  return 0;
}
