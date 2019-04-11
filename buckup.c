/**
  854003 山内龍我 自由課題 3D表現
  ver.1.3
**/

#include<stdio.h>
#include<math.h>
#include<handy.h>
#define WindowSize 500

//グローバル変数
float X[8] = {};     //各X軸情報を格納する
float Y[8] = {};     //各Y軸情報を格納する
int originX = 250;   //固定のX軸（原点の設定）
int originY = 150;   //固定のY軸（原点の設定）
float angle = 0;     //角度（変動）
int radX = 100;      //X軸半径
int radY = 50;       //Y軸半径

int main(){

  doubleLayer layers;  //ダブルバッファ用のデータ
  int windowID;        //ウィンドウの番号
  int layerID;         //レイヤーの番号
  int i = 0;           //カウンタ
  int add = -90;         //角度変更
  int color = 0;       //頂点の色指定

  for(i=0;i<8;i++){    //各XY軸の初期値代入(250)
    X[i] = originX;
    Y[i] = originY;
  }

  windowID = HgOpen(WindowSize,WindowSize);  //レイヤーをオープン
  layers = HgWAddDoubleLayer(windowID);    //ダブルバッファを作る

  while(1){

    layerID = HgLSwitch(&layers);  //表示レイヤを入れ替える
    HgLClear(layerID);              //描画用レイヤを消去する

    //X軸Y軸の計算
    for(i = 0;i<4;i++){
      X[i] = originX + cos(angle + (M_PI_2*i)) * radX;         //底辺XX軸
      Y[i] = originY + sin(angle + (M_PI_2*i)) * radY;         //底辺Y軸
      X[i+4] = originX + cos(angle + (M_PI_2 * i)) * radX;       //上辺X軸
      Y[i+4] = originY + 100 + sin(angle + (M_PI_2 * i)) * radY; //底辺Y軸
    }

    for(i = 0;i < 7;i++){
      if(i != 3)HgWLine(layerID,X[i],Y[i],X[i+1],Y[i+1]);     //下、上の1,2,3,1,2,3を描画
      if(i == 0 || i ==4) HgWLine(layerID,X[i+3],Y[i+3],X[i],Y[i]);    //下、上の4,4を描画
      if(i < 4)     HgWLine(layerID,X[i],Y[i],X[i+4],Y[i+4]);    //縦を描画
    }/*

    HgWLine(layerID,X[0],Y[0],X[1],Y[1]);    //下１ 01 i,i+1
    HgWLine(layerID,X[1],Y[1],X[2],Y[2]);    //下２ 12 i,i+1
    HgWLine(layerID,X[2],Y[2],X[3],Y[3]);    //下３ 23 i,i+1
    HgWLine(layerID,X[3],Y[3],X[0],Y[0]);    //下４   30 i==0  i+3
    HgWLine(layerID,X[4],Y[4],X[5],Y[5]);    //上１ 45 i,i+1
    HgWLine(layerID,X[5],Y[5],X[6],Y[6]);    //上２ 56 i,i+1
    HgWLine(layerID,X[6],Y[6],X[7],Y[7]);    //上３ 67 i,i+1
    HgWLine(layerID,X[7],Y[7],X[4],Y[4]);    //上４   74 i ==4 i+3
    HgWLine(layerID,X[0],Y[0],X[4],Y[4]);    //縦１ 04 i,i+4
    HgWLine(layerID,X[1],Y[1],X[5],Y[5]);    //縦２ 15 i,i+4
    HgWLine(layerID,X[2],Y[2],X[6],Y[6]);    //縦３ 26 i,i+4
    HgWLine(layerID,X[3],Y[3],X[7],Y[7]);    //縦４ 37 i,i+4*/

    //色の指定
    for(int i =0;i<8;i++){
      if(i == 0) HgWSetFillColor(layerID,HG_RED);
      if(i == 1) HgWSetFillColor(layerID,HG_BLUE);
      if(i == 2) HgWSetFillColor(layerID,HG_YELLOW);
      if(i == 3) HgWSetFillColor(layerID,HG_GREEN);
      if(i == 4) HgWSetFillColor(layerID,HG_PURPLE);
      if(i == 5) HgWSetFillColor(layerID,HG_BLACK);
      if(i == 6) HgWSetFillColor(layerID,HG_WHITE);
      if(i == 7) HgWSetFillColor(layerID,0xc71585);
      HgWCircleFill(layerID,X[i],Y[i],5,1);
    }


    angle += 0.1;    //頂点の移動に使う角度

    printf("%f,%f,%f\n",X[0],Y[0],angle); //デバッグ
    HgSleep(0.1);

  }
  HgClose();
  return 0;
}
