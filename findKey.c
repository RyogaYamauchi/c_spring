#include<stdio.h>

int main(){
  int id[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  int key[10] = {114, 194, 223, 315, 326, 404, 514, 634, 777, 819};
  int i;
  int num;
  int cnt=0;

  printf("IDを入力してください");
  scanf("%d",&num);

  for(i=0;i<10;i++){
    if(num == id[i]){
      break;
    }
    cnt++;
  }
  if(cnt > 9) {
    printf("IDが見つかりません");
  }
  else{
    printf("ID %d さんのパスワードは%dです\n",num,key[cnt]);
  }
  return 0;
}
