#include<stdio.h>
int main(){
  char number1[10];
  char number2[10];
  char number3[10];
  char number4[10];
  char number5[10];
  char number6[10];
  char number7[10];

  printf("これから心理テストを始めます。\n");
  printf("あなたは美しい森の中にいます。太陽はキラキラと輝き、風があなたの頬を気持ちよくなでています。\n");
  printf("Q1.誰と一緒に歩いていますか？\n");
  scanf("%s",number1);
  printf("\nあなたは誰かと一緒に森の中を歩き続けていくと、ある動物に出会います。\n");
  printf("Q2.その動物は一体何ですか？\n");
  scanf("%s",number2);
  printf("\nさらに深く森の中を進むと空き地に出ました。その中心には、一軒の家があります。\n");
  printf("Q3.見つけた家はどれくらいの大きさ？その家に、フェンスはありますか？\n");
  scanf("%s",number3);
  printf("\nに近づいてみたところ、ドアが少し開いていました。そっと中へ入るとそこにはテーブルがありました。\n");
  printf("Q4.テーブルの上には何が置かれていますか？\n");
  scanf("%s",number4);
  printf("\nあなたは家の中をひと通り見て、裏口から外に出ます。そこには芝生が広がっていて、中心には庭があります。そこで、あなたはマグカップを見つけます。\n");
  printf("Q5.マグカップは何で出来ていますか？\n");
  scanf("%s",number5);
  printf("\n庭を進み続けると、あなたは自分が水の中にいることに気付きます。\n");
  printf("Q6.それは、湖ですか？川ですか？池ですか？\n");
  scanf("%s",number6);
  printf("\n家に帰るためには、その水の中を渡りきらなければなりません。\n");
  printf("Q7.どれぐらい濡れてしまいましたか？\n");
  scanf("%s",number7);

  printf("\n\n\n\nQ1.森の中を一緒に歩いているのは、人生で一番大切な人です。\nQ2.出会った動物の大きさは、抱えている問題の大きさを示しています。\nもし、その動物が警戒心が強く、近寄りがたいようであれば、あなたは積極的な人です。\n逆に、のほほんとした平和的な雰囲気であれば、受け身の傾向があるでしょう。\nQ3.家の大きさは、野心の強さを示しています。\nフェンスがあるか無いかは、あなたが開放的な性格かどうかを示しています。\n無い人は、より素直な性格です。\nQ4.テーブルの上に、食べ物や人、または花を見つけた人は、幸せだと感じている可能性が高いです。\nそれらが無かった人は、あまり幸せではないのかも…！？\nQ5.マグカップがどれほど丈夫であるかによって、森の中を一緒に歩く人との関係の強さが分かります。\nまた、それを使って何をするかは、あなたがその人に対し、どのような態度を取るかを表しています。\nQ6.湖か、川か、池か…その大きさは、あなたの性欲の強さです。\nQ7.水に濡れた程度で、あなたがセックスをどれほど重要しているかが分かります。\n濡れている方が、重要視しているとか…。 ");
  printf("あなたが選んだ選択は%s,\n%s,%s,\n%s,\n%s,\n%s,\n%sでした。",number1,number2,number3,number4,number5,number6,number7);
  printf("お疲れ様でした\n");

}