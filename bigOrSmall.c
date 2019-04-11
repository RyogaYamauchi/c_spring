#include<stdio.h>

int main(){

  int num1;
  int num2;

  printf("１つめの数字を入力してください：");
  scanf("%d",&num1);
  printf("２つめの数字を入力してください：");
  scanf("%d",&num2);

  if(num1 > num2){
    printf("%dは%dより大きい\n",num1,num2);
  }
  else if(num1 < num2){
    printf("%dは%dより小さい\n",num1,num2);
  }
  else{
    printf("%dは%dと等しい\n",num1,num2);
  }


}
