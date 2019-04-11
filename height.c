#include<stdio.h>

int main(){
  int num;
  int array[5] = {163,157,176,180,166};
  printf("input number :");
  scanf("%d",&num);

    printf("%d番の身長は%dです。",num,array[num]);
  return 0;
}
