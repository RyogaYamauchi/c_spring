#include<stdio.h>

int main(){
  int num;
  int i;

  printf("input number : ");
  scanf("%d",&num);

  for(i=1;i<=num;i++){
    if(i%3 != 0) printf("%d\n",i);
    if(i%3 == 0) printf("fizz\n");
  }
  return 0;
}
