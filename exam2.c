#include<stdio.h>

int main(){
  int num;

  printf("数字を入力してください");
  scanf("%d",&num);

  if(num>=90){
    printf("秀\n");
  }
  else if(num>=80){
    printf("優\n");
  }
  else if(num>=70){
    printf("良\n");
  }
  else if(num>=60){
    printf("可\n");
  }
  else{
    printf("不可\n");
  }
}
