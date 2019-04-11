#include<stdio.h>

int main(){
  int array[15];
  int i;

  array[0] = 1;

  for(i=1;i<15;i++){
    array[i] = 3*array[i-1]+2;

  }

  for(i=14;i>=0;i--){
    printf("%d\n",array[i]);
  }
}
