/*
 854003 山内龍我
*/

#include<stdio.h>
#include<handy.h>

int main(){
  int inputNum1;   //入力用変数（四角形の左下x座標） 220
  int inputNum2;   //入力用変数（四角形の左下y座標） 200
  int inputNum3;   //入力用変数（四角形の右上x座標） 450
  int inputNum4;   //入力用変数（四角形の右上x座標） 320

  int halfx;       //入力されたx座標の半分の値
  int halfy;       //入力されたy座標の半分の値


    printf("input x0 : ");
    scanf("%d",&inputNum1);
    printf("input y0 : ");
    scanf("%d",&inputNum2);
    printf("input x1 : ");
    scanf("%d",&inputNum3);
    printf("input y1 : ");
    scanf("%d",&inputNum4);

    HgOpen(600,600);

    halfx = (inputNum3 - inputNum1)/2;
    halfy = (inputNum4 - inputNum2)/2;


    HgBox(inputNum1,inputNum2,inputNum3-inputNum1,inputNum4-inputNum2);           //四角形の描画
    HgLine(inputNum1-halfx,inputNum2+halfy,inputNum1+halfx,inputNum2-halfy);      //ひし形の描画
    HgLine(inputNum1+halfx,inputNum2-halfy,inputNum1+halfx*3,inputNum2+halfy);    //ひし形の描画
    HgLine(inputNum1+halfx*3,inputNum2+halfy,inputNum1+halfx,inputNum2+halfy*3);  //ひし形の描画
    HgLine(inputNum1+halfx,inputNum2+halfy*3,inputNum1-halfx,inputNum2+halfy);    //ひし形の描画
    HgBox(inputNum1-halfx,inputNum2-halfy,halfx*4,halfy*4);                       //大きい方の四角形の描画

    HgGetChar();
    HgClose();

    return 0;
}
