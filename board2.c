#include<stdio.h>

int main(){
  int array[9][9]={};
  int i,j;

  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(i==j) {
        array[i][j]=1;
      }
      else if (i+j==8){
        array[i][j]=1;
      }
      else{
        array[i][j]=0;
      }
      printf("%d ",array[i][j]);
    }
    printf("\n");
  }

  return 0;
}
