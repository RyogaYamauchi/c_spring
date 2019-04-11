/**
  854003 山内龍我 自由課題
  3D表現　機能：拡大縮小、Y軸回転、移動、回転ループ
  機能の変更は、左上にあるボタンを押すことで変わります。

   2018.6.21 - 2018.7.5 ver.1.6
**/

#include<stdio.h>
#include<math.h>
#include<handy.h>
#define WindowSize 500

/**  グローバル変数  **/
float X[8] = {};       //各X軸情報を格納する(描画処理)
float Y[8] = {};       //各Y軸情報を格納する(描画処理)
float angle = 0;       //角度（変動）　　　 (回転)
float mag = 1.0;       //ドラッグの倍率　　 (拡大縮小)
float PublicMag = 0;   //ドラッグ時の比率取得
float moveX,moveY;     //移動するための変数
float backEvent  = 0.0;//ドラッグ時、前にマウスのあった位置を保存する
int originX = 250;     //固定のX軸（原点の設定）
int originY = 150;     //固定のY軸（原点の設定）
int radX = 100;        //X軸半径
int radY = 50;         //Y軸半径
int height = 100;      //高さ
int cnt = 0;           //mode表示を一度だけするための変数
int mode = 0;          //各モード変更のためのスイッチ変数

/** プロトタイプ宣言 **/
int Spin();         //ずっと回り続ける
int Scale();        //拡大縮小
int Rotate(float);  //回転
int move();         //移動
int writeMode(int); //モード切り替え時の文字変更

/** メイン処理 **/
int main(){
  doubleLayer layers;    //ダブルバッファ用のデータ
  int windowID;          //ウィンドウの番号
  int layerID;           //レイヤーの番号
  int add = -90;         //角度変更
  int i =0;              //カウンタ
  int color[8] = {0x6e6fa,0x708090,0x000080,0x006400,0xff0000,0xff69b4,0xffa500,0x7fff00};       //頂点の色指定

  windowID = HgOpen(WindowSize,WindowSize);                  //レイヤーをオープン
  layers = HgWAddDoubleLayer(windowID);                      //ダブルバッファを作る
  HgWSetEventMask(layerID,HG_MOUSE_DRAG | HG_MOUSE_DOWN );   //ドラッグとクリックを検出
  HgSetFont(HG_M, 18);                                       //フォントを明朝体、サイズを18に設定
  HgText(300,450,"mode : ");                                 //modeの初期表示
  writeMode(0);                                              //最初はSpin

  Spin();  //初期値代入用

  /** メイン処理 **/
  while(1){

    layerID = HgLSwitch(&layers);            //表示レイヤを入れ替える
    HgLClear(layerID);                       //描画用レイヤを消去する
    hgevent *event = HgEventNonBlocking();   //イベントを取得

    /** イベント処理（ドラッグ・クリック） **/
    if(event != NULL){
      if (event->type == HG_MOUSE_DRAG) {    //ドラッグ処理
        PublicMag = (event->y / WindowSize); //ドラッグ時の比率取得
        moveX = event->x;     //ドラッグしているxの値
        moveY = event->y;     //ドラッグしているyの値
        switch(mode){         //モード切り替え
          case 0 : Spin();    //回転モードに切り替え
                   break;
          case 1 : Scale();   //拡大縮小モードに切り替え
                   break;
          case 2 : Rotate(moveX);  //回転モードに切り替え
                   break;
          case 3 : move();    //移動モードに切り替え
                   break;
          default: printf("IOExeption\n");  //バグ発生
        }
      printf("in a DRAG %f\n",angle);       //ドラッグをしているときの処理
      backEvent = event->x;                 //前のドラッグ位置を保存
      }
      if(event->type == HG_MOUSE_DOWN){    //クリック処理
        if(event->x > 10 && event->x < 30 && event->y > 475 && event->y < 495) mode = 1; writeMode(mode);   //拡大縮小モードに切り替え
        if(event->x > 40 && event->x < 60 && event->y > 475 && event->y < 495) mode = 2; writeMode(mode);   //回転モードに切り替え
        if(event->x > 70 && event->x < 90 && event->y > 475 && event->y < 495) mode = 3; writeMode(mode);   //移動モードに切り替え
        if(event->x > 100 && event->x < 120 && event->y > 475 && event->y < 495) mode = 0; writeMode(mode); //スピンモードに切り替え
      }
    }
    else{
      if(mode == 0)Spin();    //一番最初はスピンから
    }

    /** 左上のモード切り替え用の正方形描画 **/
    HgWSetFillColor(layerID,HG_GREEN);   //拡大縮小
    HgWBoxFill(layerID,10,475,20,20,1);
    HgWSetFillColor(layerID,HG_BLUE);    //回転
    HgWBoxFill(layerID,40,475,20,20,1);
    HgWSetFillColor(layerID,HG_YELLOW);  //移動
    HgWBoxFill(layerID,70,475,20,20,1);
    HgWSetFillColor(layerID,HG_PURPLE);  //スピン
    HgWBoxFill(layerID,100,475,20,20,1);

    /** オブジェクト描画処理 **/
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

    HgSleep(0.1);    //描画速度
    //printf("%f,%f,%f\n",X[0],Y[0],angle); //デバッグ
  }
  return 0;
}

/** ずっと回り続ける **/
int Spin(){
  int i = 0;
  /** X軸Y軸の計算 **/
  for(i = 0;i<4;i++){
    X[i] = originX + cos(angle   + (M_PI_2*i)) * radX * mag;                       //底辺X軸
    Y[i] = originY + sin(angle  + (M_PI_2*i)) * radY * mag;                       //底辺Y軸
    X[i+4] = originX + cos(angle +  (M_PI_2 * i)) * radX * mag;                   //上辺X軸
    Y[i+4] = originY + (height * mag) + sin(angle  + (M_PI_2 * i)) * radY * mag;  //底辺Y軸
  }
  angle += 0.1;    //頂点の移動に使う角度
  printf("in a Spin\n");
  return 0;
}

/** 拡大縮小 **/
int Scale(){
  int i =0;
  mag = PublicMag;    //Scaleの処理が回ってる時だけ値を変更するため
  for(i = 0;i<4;i++){
    X[i] = originX + cos(angle + (M_PI_2*i)) * radX * mag;                    //底辺X軸
    Y[i] = originY + sin(angle + (M_PI_2*i)) * radY * mag;                     //底辺Y軸
    X[i+4] = originX + cos(angle  + (M_PI_2*i)) * radX * mag;                   //上辺X軸
    Y[i+4] = originY + (height * mag) + sin(angle + (M_PI_2*i)) * radY * mag;  //底辺Y軸
  }
  printf("mag = %f\n",mag);  //デバッグ
  printf("in a Scale\n");    //デバッグ
  return 0;
}

/** 回転 **/
int Rotate(float moveX){
  int i = 0;
  for(i = 0;i<4;i++){
    X[i] = originX + cos(angle + (M_PI_2*i)) * radX * mag;                       //底辺X軸
    Y[i] = originY + sin(angle+ (M_PI_2*i)) * radY * mag;                       //底辺Y軸
    X[i+4] = originX + cos(angle + (M_PI_2 * i)) * radX * mag;                   //上辺X軸
    Y[i+4] = originY + (height * mag) + sin(angle + (M_PI_2 * i)) * radY * mag;  //底辺Y軸
  }
  printf("X[4] = %f",X[4]);
  printf("in a Rotate\n");
  if(backEvent <= moveX){    //ドラッグで右回り
    angle+= 0.1;
  }
  if(backEvent >= moveX){    //ドラッグで左回り
    angle-= 0.1;
  }
  printf("backEvent = %f, moveX = %f",backEvent,moveX);    //デバッグ
  return 0;
}

/** 移動 **/
int move(){
  int i = 0;
  originX = moveX;  //移動の情報を他の機能に反映させるためのX
  originY = moveY;  //移動の情報を他の機能に反映させるためのX
  for(i = 0;i<4;i++){
    X[i] = originX  + cos(angle  + (M_PI_2*i)) * radX * mag;                   //底辺X軸
    Y[i] = originY + sin(angle + (M_PI_2*i)) * radY * mag;                     //底辺Y軸
    X[i+4] = originX + cos(angle + (M_PI_2*i)) * radX * mag;                   //上辺X軸
    Y[i+4] = originY + (height * mag) + sin(angle + (M_PI_2*i)) * radY * mag;  //底辺Y軸
    }
  printf("X = %f\n",X[0]);   //デバッグ
  printf("in a move\n");     //デバッグ
  return 0;
}

/** モード切り替え時の表示切り替え **/
int writeMode(int num){        //引数：モードの値
  int i = 0;
  HgBoxFill(365,450,60,30,1);  //空白に初期化
  if(num == 0){                //Spin
     HgText(370,450,"Spin");
   }
   if(num == 1){               //Scale
      HgText(370,450,"Scale");
   }
   if(num == 2){               //Rotate
     HgText(370,450,"Rotate");
   }
   if(num == 3){               //move
     HgText(370,450,"move");
  }
  cnt++;
  return 0;
}
