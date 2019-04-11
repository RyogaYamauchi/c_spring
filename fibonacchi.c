#include<stdio.h>

int main(){
  int array[20];
  int i;

  array[0]=1;
  array[1]=1;

  for(i=2;i<20;i++){
    array[i] = array[i-1] + array[i-2];
    printf("%d\n",array[i-2]);
  }
  printf("%d\n",array[18]);
  printf("%d\n",array[19]);


}
