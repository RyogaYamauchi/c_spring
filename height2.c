#include<stdio.h>

int main(){
  int num;
  int array[5] = {163,157,176,180,166};

  while(1){
    printf("input number :");
    scanf("%d",&num);
    if(num>=0 && num<=4){
      printf("%d番の身長は%dです。",num,array[num]);
      break;
    }
  }
  return 0;
}
