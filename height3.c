#include<stdio.h>

int main(){
  int num;
  int array[5] = {163,157,176,180,166};
  int i = 0;

  while(1){
    printf("input number :");
    scanf("%d",&num);
    if (num>= 54400 && num <=54404){
      break;
    }
  }
  for(i = 0;i < 5;i++){
    if(num == 54400 + i) {
      printf("%d番目の身長は%dです\n", num,array[i]);
      break;
    }
  }
  return 0;
}
