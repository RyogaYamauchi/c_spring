/*****
    add.c
    入力された2つの整数の和を表示する
    Yamauchi Ryoga
*****/
#include <stdio.h>

int main() {
    int num1;
    int num2;
    int sum;
    printf("入力された２つの数字を足して出力するプログラムです。\n数字を入力してください\n");
    scanf("%d",&num1);
    scanf("%d",&num2);
    sum = num1+num2;
    printf("%d\n",sum);
    return 0;
}
