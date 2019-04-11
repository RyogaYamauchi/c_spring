#include<stdio.h>

int main(){
  int num;
  int i;
  printf("inputNumber : ");
  scanf("%d",&num);

  for(i=num;i>0;i--){
    printf("%d\n",i);
  }
  return 0;
}
