/*
  854003 山内龍我
*/


#include<stdio.h>

int main(){

  int num;
  int i;

  int formula=1;   //式


  while(1){            //0以下が入力されたら繰り返し
    printf("input number :");
    scanf("%d",&num);
    if(num>0) break;
  }



  for(i=0;i<num;i++){
    printf("%d\n",formula);     //さきに出力しないとだめ！

    formula = formula * 3 + 2;  //漸化式

  }


  return 0;
}
