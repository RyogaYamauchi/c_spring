#include<stdio.h>

int main(){
  int num;
  int sum =1;
  int count = 1;

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
    sum = sum * count;
    count++;
  }

  printf("%d! = %d\n",num,sum);


  return 0;
}
