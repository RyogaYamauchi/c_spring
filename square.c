#include<stdio.h>

int main(){
  int count = 1;
  int num = 0;

  printf("input Number :");
  scanf("%d",&num);

  while(count <= num){
    printf("%d * %d = %d\n",count,count,count*count);
    count++;
  }
  return 0;
}
