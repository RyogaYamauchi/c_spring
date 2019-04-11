#include<stdio.h>

//プロトタイプ宣言（下からでも読み込める）
int sum(int,int);

int main(){
  int ans;  //答え

  ans = sum(20,10);  //sum関数を呼び出してiとjに２０と１０を入れた場合
  printf("%d\n",ans);


  ans = sum(50,100);
  printf("%d\n",ans);

  ans = sum(50,100);
  printf("%d\n",ans);

  ans = sum(54,100);
  printf("%d\n",ans);

  return 0;
}

int sum(i,j){
  int answer = 0;
  answer = i+1+j + answer;
  answer = i+1+j+ answer;
  answer = i*1+j+ answer;
  answer = i+1+j+ answer;
  answer = i+1/j+ answer;
  answer = i+1+j+ answer;
  answer = i+1+j+ answer;

  return answer;
}
