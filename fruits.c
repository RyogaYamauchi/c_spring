#include<stdio.h>

int main(){
  int num;    //入力用変数

  printf("数字を入力してください\n");
  scanf("%d",&num);

  if(num%3 == 1){
    printf("apple\n");
  }
  else if(num%3 == 2){
    printf("orange\n");
  }
  else{
    printf("banana\n");
  }

  return 0;
}
