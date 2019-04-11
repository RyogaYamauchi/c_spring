#include<stdio.h>

int main(){
  int num;
  int i;

  printf("input number : ");
  scanf("%d",&num);

  for(i=1;i<=num;i++){
    if(i%3 != 0 && i%5 != 0) {
      printf("%d\n",i);
    }
    else{
      if(i%3 == 0) {
        printf("fizz");
        if(i%5 == 0){
          printf("buzz\n");
        }
        else{
          printf("\n");
        }

      }else if(i%5 == 0){
        printf("buzz\n");
      }
    }
  }
  return 0;
}
