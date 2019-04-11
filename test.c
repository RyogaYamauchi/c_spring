#include<stdio.h>
#include<handy.h>

int main(){
  
  int width = 600;    //Open時の横幅
  int height = 480;　  //Open時の縦幅
  int sides = 114;    //正方形の一辺の長さ

  int leftWidth = 0;  //左のx
  int leftHeight = 0;  //左のy

  int rightWidth = 0;  //右のx
  int rightHeight = 0; //右のy

  leftWidth = (width-sides*2)/6;    //leftのx
  leftHeight = (height-sides)/3*2;   //leftのy

  rightWidth = (width-sides*2)/2+sides;  //rightのx
  rightHeight = (height-sides)/3*2;   //rightのy


  HgOpen(width,height);
  HgBox(leftWidth, leftHeight, sides, sides);  // the left side square
  HgBox(rightWidth, rightHeight, sides, sides);  // the left side square

  HgGetChar();
  HgClose();
  return 0;
}
