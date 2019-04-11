/**
  854003 山内龍我 自由課題 3D表現
**/

#include<stdio.h>
#include<math.h>
#include<handy.h>
#define WindowSize 500

/**  グローバル変数  **/
float X[8] = {};     //各X軸情報を格納する
float Y[8] = {};     //各Y軸情報を格納する
int originX = 250;   //固定のX軸（原点の設定）
int originY = 150;   //固定のY軸（原点の設定）
float angle = 0;     //角度（変動）
int radX = 50;      //X軸半径
int radY = 100;       //Y軸半径
int height  = 100;
int cnt= 0;

int main(){
  doubleLayer layers;    //ダブルバッファ用のデータ
  int windowID;          //ウィンドウの番号
  int layerID;           //レイヤーの番号
  int add = -90;         //角度変更
  int i =0;     //カウンタ
  int color[8] = {0x6e6fa,0x708090,0x000080,0x006400,0xff0000,0xff69b4,0xffa500,0x7fff00};       //頂点の色指定

  windowID = HgOpen(WindowSize,WindowSize);  //レイヤーをオープン
  layers = HgWAddDoubleLayer(windowID);      //ダブルバッファを作る

  /** メイン処理 **/
  while(1){

    layerID = HgLSwitch(&layers);   //表示レイヤを入れ替える
    HgLClear(layerID);              //描画用レイヤを消去する

    /** X軸Y軸の計算 **/
    for(i = 0;i<4;i++){
      X[i] = originX + cos(angle + (M_PI_2*i)) * radX;            //底辺X軸
      Y[i] = originY + sin(angle + (M_PI_2*i)) * radY;            //底辺Y軸
      X[i+4] = originX + cos(angle + (M_PI_2 * i)) * radX;        //上辺X軸
      Y[i+4] = originY +height +sin(angle + (M_PI_2 * i)) * radY;  //底辺Y軸
      printf("%d\n",cnt);
      cnt++;
    }

    if(cnt > 100){
      for(i = 0;i<4;i++){
        X[i] = originX + cos(angle + (M_PI_2*i)) * (radX*2);            //底辺X軸
        Y[i] = originY + sin(angle + (M_PI_2*i)) * (radY/2);            //底辺Y軸
        X[i+4] = originX + height + cos(angle + (M_PI_2 * i)) * (radX*2);        //上辺X軸
        Y[i+4] = originY +sin(angle + (M_PI_2 * i)) * (radY*2);  //底辺Y軸
        cnt++;
      }
    }

    /** 描画処理 **/
    for(i = 0;i < 7;i++){
      if(i != 3)HgWLine(layerID,X[i],Y[i],X[i+1],Y[i+1]);              //下,上の1,2,3,1,2,3を描画
      if(i == 0 || i ==4) HgWLine(layerID,X[i+3],Y[i+3],X[i],Y[i]);    //下,上の4,4を描画
      if(i < 4)     HgWLine(layerID,X[i],Y[i],X[i+4],Y[i+4]);          //縦を描画
    }

    /** 頂点となる円の描画と色の処理 **/
    for(i =0;i<8;i++){
      HgWSetFillColor(layerID,color[i]);     //色を指定
      HgWCircleFill(layerID,X[i],Y[i],5,1);  //頂点となる円の描画
    }

    angle += 0.1;    //頂点の移動に使う角度
    HgSleep(0.1);    //描画速度

    printf("%f,%f,%f\n",X[0],Y[0],angle); //デバッグ
  }
  return 0;
}
