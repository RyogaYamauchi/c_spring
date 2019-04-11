/*
  854003 山内龍我
*/

#include<stdio.h>

int main(){

  int sint;  //身長
  int taij;  //体重
  float std;  //標準体重

  printf("身長：");
  scanf("%d",&sint);
  printf("体重：");
  scanf("%d",&taij);

  std = sint - 105;      //身長に対しての標準体重

  if(std < (taij*1.1) && std > taij*0.9){
    printf("ええ感じやなぁ\n");
  }else if(std < (taij*1.1)) {
    printf("ちょっと太ってるなぁ\n");
  }else{
    printf("ちょっと痩せてるなぁ\n");
  }


  return 0;
}
