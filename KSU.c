#include<stdio.h>

int main(){
  int i;
  int j;
  int num;

  printf("input Number : ");
  scanf("%d",&num);

  for(i=0;i<num;i++){
    for(j=0;j<num;j++){
      printf("KSU ");
    }
    printf("\n");
  }
}
