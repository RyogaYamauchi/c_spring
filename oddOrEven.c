#include<stdio.h>

int main(){
  int num;    //入力用変数

  printf("数字を入力してください\n");
  scanf("%d",&num);

  if(num%2 != 0){
    printf("odd\n");
  }
  else{
    printf("even\n");
  }

  return 0;
}
