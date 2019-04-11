/** ローグライクダンジョン生成
    地形 : 0
    部屋 : 1
    道  : 2
    敵  : 3
    アイテム : 4
    階段 : 8
    自分 : 9
**/
#include <stdio.h>
#include <math.h>
#include <handy.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define terrianSizeX 54
#define terrianSizeY 36
#define WindowWidth 1080
#define WindowHeight 720
#define charctorSize 10
#define magnification 20  //倍率

//構造体宣言
typedef struct charctor{
  int x;
  int y;
  int hp;
  int Lv;
  int Exp;
  int moveFlag;
  int attack;
  int defence;
  int ID;

}charctor;

//プロトタイプ宣言
int getRoom();                       //部屋の情報を取得
int grid();                          //仮のグリッド線を描画
int getRoot();                       //部屋と部屋の道を取得
int getRootRight(int,int);           //部屋と部屋の道を取得（横）
int getRootUp(int,int);              //部屋と部屋の道を取得（縦)
int CharctorController(charctor*);   //キャラクターのアクションを操作
int moveRight(charctor*);            //右に移動（キャラクターであれば可能
int moveLeft(charctor*);             //左に移動　
int moveUp(charctor*);               //上に移動
int moveDown(charctor*);             //下に移動
int regulation();                    //ダンジョン生成後の位置調整
int UIController();                  //UIを操作する
int AppearEnemy(int);                //X,Y,hpを引数にとり、ランダムで出現
int WriteTerrian();                  //地形生成をまとめた
int enemyAI(charctor*);              //敵のAI
int Damage(charctor*,int);               //引数に取るキャラクターに１ダメージを与える
int CheckRoom(charctor**);           //引数に取ったキャラクターの部屋番号を調べる
int attack(charctor*);               //引数に取ったキャラクターの方向にいるキャラクターに１ダメージ与える
int gameController();                //ゲーム画面を操作する
int logContoller(char*);             //ログ画面を操作する
int attackAnimationRight(charctor**);
int attackAnimationLeft(charctor**);
int attackAnimationUp(charctor**);
int attackAnimationDown(charctor**);

//グローバル変数
int Room[9][4] = {};                 //部屋の情報を保持(x,y,width,height)
int roomX[9]   = {};                 //部屋の大きさX
int roomY[9]   = {};                 //部屋の大きさY
int iniRoomX[9]= {};                 //部屋の初期位置を少しずらすX
int iniRoomY[9]= {};                 //部屋の初期位置を少しずらすY
int layerID;                         //ベースレイヤーの番号
int terrian[terrianSizeX][terrianSizeY];  //地形情報
int charctorLayer;                   //キャラクターを描画するレイヤー
int UILayer;                         //別ウィンドウのUIを描画するレイヤー
int logLayer;                        //ログのレイヤー
int enemyCount    = 1;               //敵の初期値
charctor player   = {10,10,10,1,1,1,1,1};  //プレイヤーを定義
charctor enemy[6] = {};              //敵を定義
int Root[9][4][2] = {};              //道の情報を保持
int stepX = 0;                       //階段を降りるx
int stepY = 0;                       //階段を降りるy
int gameID;                          //プレイ画面のID
int gameLayer;                       //プレイ画面のレイヤー
int tempExp  = 1;                    //経験値テーブル
int MAXHP    = 10;                   //最大HP
int level    = 0;                    //階層
int logCount = 0;                    //Logの数
char logStore[100];                  //ログの情報
char logStoreTemp[100];              //ログの情報（変数）
char store[10][100];                 //ログを貯める配列
int logID;                           //ログのID
int cureTime = 0;
int animationLayer;

int main(void){
  doubleLayer layers;      //ダブルバッファ用のデータ
  int i,j;                 //カウンタ
  int windowID;            //ベースウィンドウの番号
  int UIID;                //UIのウィンドウ番号
  int enemyID = 0;         //敵のID

  windowID = HgOpen(WindowWidth,WindowHeight);    //ベースレイヤーをオープン
  layerID = HgWAddLayer(windowID);                //ベースレイヤーをオープン
  HgWSetTitle(windowID,"全体マップ");
  logID = HgWOpen(200,100,1000,200);              //ログレイヤーをオープン
  logLayer = logID;                               //ログレイヤーをオープン
  HgWSetTitle(logID,"ログ");
  UIID = HgWOpen(300,1300,150,100);               //UIレイヤーをオープン
  UILayer = UIID;                                 //UIレイヤーをオープン
  HgWSetTitle(UIID,"プレイヤー情報");
  gameID = HgWOpen(600,350,600,400);              //ゲーム画面レイヤーをオープン
  gameLayer = gameID;                             //ゲーム画面レイヤーをオープン
  HgWSetTitle(gameID,"プレイ画面");
  animationLayer = HgWAddLayer(gameID);

  HgWSetEventMask(gameID,HG_KEY_DOWN);           //ドラッグとクリックを検出
  WriteTerrian();
  charctorLayer = HgWAddLayer(layerID);           //キャラクターレイヤーをオープン
  terrian[10][10] = 9;                            //プレイヤーの初期位置

  for(i=1;i<6;i++){
    enemy[i].hp = 0;
  }

  while(1){  //メイン処理
    hgevent *event = HgEvent();              //イベントを取得
    if (event->type == HG_KEY_DOWN) {        //イベント判定
      switch (event->ch) {
        case 119: moveUp(&player);               //w（前に進む）
                  player.moveFlag = 1;
                  break;
        case 97:  moveLeft(&player);             //a（左に進む）
                  player.moveFlag = 2;
                  break;
        case 115: moveDown(&player);             //s（下に進む）
                  player.moveFlag = 3;
                  break;
        case 100: moveRight(&player);            //d（右に進む）
                  player.moveFlag = 0;
                  break;
        case 101: attack(&player);               //Eキーで攻撃
                  break;
        case 108:                                //lキーでチート
                 //新しくダンジョン生成の際の初期化
                 WriteTerrian();
                 break;
        defalut: break;
        }
        if(stepX == player.x && stepY == player.y) WriteTerrian(); //階段を降りる
    }

    if(enemyCount<6){  //最大５体まで敵が出現
      if(enemy[enemyID].ID != enemyID){  //すでに敵が存在していなかった時
        AppearEnemy(enemyID);
      }
    }
    enemyID++;
    if(enemyID>5)enemyID=1;

    HgLClear(charctorLayer);
    CharctorController(&player);    //キャラクターのアクションを操作
    for(i=1;i<6;i++){     //敵の数だけ敵を描画
      enemyAI(&enemy[i]);
      CharctorController(&enemy[i]);
    }
    UIController();
    if(player.hp<MAXHP){
      if(cureTime%3==0) player.hp++;
    }
    cureTime++;
    gameController();
  }
}

//引数に取ったx,yの場所にいる敵のIdを返す
int checkID(int x,int y){
  int ID,i;
  for(i=1;i<enemyCount;i++){
    if(x == enemy[i].x && y == enemy[i].y){
      return enemy[i].ID;
    }
  }
  return ID;
}

//引数に入れたポケモンの向いてる方向に1ダメージを与える
int attack(charctor *charctor){
  int i,j,ID;
  if(charctor->moveFlag == 0) {
    if(terrian[charctor->x+1][charctor->y] == 3){
      ID = checkID(charctor->x+1,charctor->y);
      for(i=1;i<enemyCount;i++){
        if(enemy[i].ID == ID) Damage(&enemy[i],player.attack);
      }
    }
    attackAnimationRight(&charctor);
    strcpy(logStore,"プレイヤーの右への攻撃");
    logContoller(logStore);
  }
  if(charctor->moveFlag == 1) {
    if(terrian[charctor->x][charctor->y+1] == 3){
      ID = checkID(charctor->x,charctor->y+1);
      for(i=1;i<enemyCount;i++){
        if(enemy[i].ID == ID) Damage(&enemy[i],player.attack);
      }
    }
    attackAnimationUp(&charctor);
    strcpy(logStore,"プレイヤーの上への攻撃");
    logContoller(logStore);
  }
  if(charctor->moveFlag == 2) {
    if(terrian[charctor->x-1][charctor->y] == 3){
      ID = checkID(charctor->x-1,charctor->y);
      for(i=1;i<enemyCount;i++){
        if(enemy[i].ID == ID) Damage(&enemy[i],player.attack);
      }
    }
    attackAnimationLeft(&charctor);
    strcpy(logStore,"プレイヤーの左への攻撃");
    logContoller(logStore);
  }
  if(charctor->moveFlag == 3) {
    if(terrian[charctor->x][charctor->y-1] == 3){
      ID = checkID(charctor->x,charctor->y-1);
      for(i=1;i<enemyCount;i++){
        if(enemy[i].ID == ID) Damage(&enemy[i],player.attack);
      }
    }
    attackAnimationDown(&charctor);
    strcpy(logStore,"プレイヤーの下への攻撃");
    logContoller(logStore);
  }

  return 0;
}

int attackAnimationRight(charctor **charctor){
  int i,x,y;
  x = 16-player.x-(*charctor)->x;
  y = 10-plpayer.y-(*charctor)->y;
  printf("charctor.x : %d, charctor.y : %d",x,y);
  if((*charctor)->Exp >= 1){
    HgWSetFillColor(gameLayer,HG_WHITE);
    HgWBoxFill(gameLayer,(14*magnification),(8*magnification),magnification*2,magnification*2,0);  //プレイヤー
    HgWSetFillColor(animationLayer,HG_BLUE);
    for(i=0;i<20;i+=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-20+i,(10*magnification)-20,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
    for(i=20;i>0;i-=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-i,(10*magnification)-20,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
  }
  else{
    HgWSetFillColor(gameLayer,HG_WHITE);
    HgWBoxFill(gameLayer,(x*magnification),(y*magnification),magnification*2,magnification*2,0);  //プレイヤー
    HgWSetFillColor(animationLayer,HG_RED);
    for(i=0;i<20;i+=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(x*magnification)-20+i,(y*magnification)-20,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
  }
  HgLClear(animationLayer);
  return 0;
}

int attackAnimationLeft(charctor **charctor){
  int i;
  if((*charctor)->Exp >= 1){
    HgWSetFillColor(gameLayer,HG_WHITE);
    HgWBoxFill(gameLayer,(14*magnification),(8*magnification),magnification*2,magnification*2,0);  //プレイヤー
    HgWSetFillColor(animationLayer,HG_BLUE);
    for(i=20;i>0;i-=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-20-i,(10*magnification)-20,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
    for(i=0;i<20;i+=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-40+i,(10*magnification)-20,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
  }
    HgLClear(animationLayer);
  return 0;
}

int attackAnimationUp(charctor **charctor){
  int i;
  if((*charctor)->Exp >= 1){
    HgWSetFillColor(gameLayer,HG_WHITE);
    HgWBoxFill(gameLayer,(14*magnification),(8*magnification),magnification*2,magnification*2,0);  //プレイヤー
    HgWSetFillColor(animationLayer,HG_BLUE);
    for(i=20;i>0;i-=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-20,(10*magnification)-20+i,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
    for(i=0;i<20;i+=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-20,(10*magnification)-i,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
  }
  HgLClear(animationLayer);
  return 0;
}

int attackAnimationDown(charctor **charctor){
  int i;
  if((*charctor)->Exp >= 1){
    HgWSetFillColor(gameLayer,HG_WHITE);
    HgWBoxFill(gameLayer,(14*magnification),(8*magnification),magnification*2,magnification*2,0);  //プレイヤー
    HgWSetFillColor(animationLayer,HG_BLUE);
    for(i=20;i>0;i-=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-20,(10*magnification)-20-i,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
    for(i=0;i<20;i+=2){
      HgLClear(animationLayer);
      HgWCircleFill(animationLayer,(16*magnification)-20,(10*magnification)-40+i,charctorSize*2,1);  //プレイヤー
      HgSleep(0.005);
    }
  }
  HgLClear(animationLayer);
  return 0;
}

int logContoller(char *strLog){
  int i;
  char temp[100];
  HgLClear(logLayer);
  strcpy(store[0],strLog);
  if(logCount<10)logCount++;
  for(i=logCount-1;i>0;i--){
    strcpy(store[i],store[i-1]);
  }
  for(i=1;i<logCount;i++){
    HgWText(logLayer,10,5+(i*20),store[i]);
  }
  return 0;
}

//引数に入れたポケモンに１ダメージを与える
int Damage(charctor *charctor,int damage){
  if(charctor->Exp >0){
    snprintf(logStore,100,"プレイヤーは%dダメージを食らった",damage);
    logContoller(logStore);
  }
  charctor->hp-=damage;
  return 0;
}

//プレイ画面の操作
int gameController(){
  int i,j,width,height,magGame;
  magGame = magnification*2;
  HgWSetFillColor(gameLayer,HG_BLACK);
  HgWBoxFill(gameLayer,0,0,600,400,0);

  width = 0;
  height = 0;
  HgWSetFillColor(gameLayer,HG_BLUE);
  for(i=player.x-7;i<player.x+8;i++){
    for(j=player.y-4;j<player.y+6;j++){
      if(terrian[i][j]==1){  //部屋の中
        HgWSetFillColor(gameLayer,HG_WHITE);
        HgWBoxFill(gameLayer,width,height,magGame,magGame,0);
      }
      else if(terrian[i][j]==2){  //道の中
        HgWSetFillColor(gameLayer,HG_WHITE);
        HgWBoxFill(gameLayer,width,height,magGame,magGame,0);
      }
      else if(terrian[i][j]==3){  //敵の場合
        HgWSetFillColor(gameLayer,HG_WHITE);
        HgWBoxFill(gameLayer,width,height,magGame,magGame,0);
        HgWSetFillColor(gameLayer,HG_RED);
        HgWCircleFill(gameLayer,width+20,height+20,charctorSize*2,1);
      }
      else if(terrian[i][j]==9){  //部屋の中
        HgWSetFillColor(gameLayer,HG_WHITE);
        HgWBoxFill(gameLayer,width,height,magGame,magGame,0);
      }
      height+=magGame;
    }
    height=0;
    width+=magGame;
  }
  HgWSetFillColor(gameLayer,HG_BLUE);
  HgWCircleFill(gameLayer,(16*magnification)-20,(10*magnification)-20,charctorSize*2,1);  //プレイヤー

  return 0;
}

//敵AI
int enemyAI(charctor *charctor){
  int i,j,room,playerRoom,enemyRoom,branch;
  int targetX,targetY;
  struct charctor *temp;
  temp = &player;
  playerRoom = CheckRoom(&temp);
  enemyRoom  = CheckRoom(&charctor);
  if(terrian[charctor->x+1][charctor->y]==9 || terrian[charctor->x][charctor->y+1]==9||terrian[charctor->x][charctor->y-1]==9){  //周囲にプレイヤーが入れば攻撃
    attack(&charctor);
    return 0;
  }
  if(playerRoom == enemyRoom) {  //同じ部屋の中にプレイヤーがいるときターゲットの設定
    if (playerRoom != 0 && enemyRoom != 0){
      targetX = player.x;
      targetY =  player.y;
    }

  }
  else{          //同じ部屋の中にプレイヤーがいないときのターゲット設定
    switch (enemyRoom) {
      case 1:    targetX = Root[enemyRoom-1][1][0];
                 targetY = Root[enemyRoom-1][1][1];
                 break;
      case 2:    targetX = Root[enemyRoom-1][2][0];
                 targetY = Root[enemyRoom-1][2][1];
                 break;

      case 3:    targetX = Root[enemyRoom-1][2][0];
                 targetY = Root[enemyRoom-1][2][1];
                 break;
      case 4:    targetX = Root[enemyRoom-1][1][0];
                 targetY = Root[enemyRoom-1][1][1];
                 break;
      case 5:
                 srand(time(NULL));
                 branch = rand()%4;
                 targetX = Root[enemyRoom-1][branch][0];
                 targetY = Root[enemyRoom-1][branch][1];
                 break;
      case 6:    targetX = Root[enemyRoom-1][3][0];
                 targetY = Root[enemyRoom-1][3][1];
                 break;
      case 7:    targetX = Root[enemyRoom-1][0][0];
                 targetY = Root[enemyRoom-1][0][1];
                 break;
      case 8:    targetX = Root[enemyRoom-1][0][0];
                 targetY = Root[enemyRoom-1][0][1];
                 break;
      case 9:    targetX = Root[enemyRoom-1][3][0];
                 targetY = Root[enemyRoom-1][3][1];
                 break;
      default : //道に出た時の処理
                 if(charctor->moveFlag == 2 && terrian[charctor->x-1][charctor->y]==2 ){  //左に行きたい
                  targetX = charctor->x-1;
                  targetY = charctor->y;
                 }
                 else if(charctor->moveFlag == 1 &&terrian[charctor->x][charctor->y+1]==2){  //上に行きたい
                   targetX = charctor->x;
                   targetY = charctor->y+1;
                 }
                 else if(charctor->moveFlag == 0 && terrian[charctor->x+1][charctor->y]==2){ //右に行きたい
                   targetX = charctor->x+1;
                   targetY = charctor->y;
                 }
                 else if(charctor->moveFlag == 3 && terrian[charctor->x][charctor->y-1]==2){  //下に行きたい
                   targetX = charctor->x;
                   targetY = charctor->y-1;
                 }

                 else if(terrian[charctor->x+1][charctor->y]==1 || terrian[charctor->x+1][charctor->y]==2){  //右に動きたい
                   targetX = charctor->x+1;
                   targetY = charctor->y;
                 }
                 else if(terrian[charctor->x][charctor->y-1]==1 || terrian[charctor->x][charctor->y-1]==2){  //下に行きたい
                   targetX = charctor->x;
                   targetY = charctor->y-1;
                 }
                 else if(terrian[charctor->x-1][charctor->y]==1 || terrian[charctor->x-1][charctor->y]==2){  //左に動きたい
                   targetX = charctor->x-1;
                   targetY = charctor->y;
                 }
                 else if(terrian[charctor->x][charctor->y+1]==1 || terrian[charctor->x][charctor->y+1]==2){  //上に行きたい
                   targetX = charctor->x;
                   targetY = charctor->y+1;
                 }

                 break;
               }

      }
    if((terrian[charctor->x-1][charctor->y]==1 ||terrian[charctor->x-1][charctor->y]==2) && targetX<charctor->x){
      moveLeft(charctor);
    }
    else if((terrian[charctor->x+1][charctor->y]==1 ||terrian[charctor->x+1][charctor->y]==2) && targetX>charctor->x){
      moveRight(charctor);
    }
    else if((terrian[charctor->x][charctor->y-1]==1 ||terrian[charctor->x][charctor->y-1]==2 )&& targetY<charctor->y){
      moveDown(charctor);
    }
    else if((terrian[charctor->x][charctor->y+1]==1 ||terrian[charctor->x][charctor->y+1]==2 )&& targetY>charctor->y){
      moveUp(charctor);
    }
  return 0;
}

//キャラの部屋の場所を確認する
int CheckRoom(charctor **charctor){
  int x,y;
  x = (*charctor)->x;
  y = (*charctor)->y;
  if      (x>Room[8][0] && y>Room[8][1] && x<Room[8][0]+1+Room[8][2] && y<Room[8][1]+1+Room[8][3]){   //9
    return 9;
  }else if(x>Room[7][0] && y>Room[7][1] && x<Room[7][0]+1+Room[7][2] && y<Room[7][1]+1+Room[7][3]){   //8
    return 8;
  }else if(x>Room[6][0] && y>Room[6][1] && x<Room[6][0]+1+Room[6][2] && y<Room[6][1]+1+Room[6][3]){    //7
    return 7;
  }else if(x>Room[5][0] && y>Room[5][1] && x<Room[5][0]+1+Room[5][2] && y<Room[5][1]+1+Room[5][3]){   //6
    return 6;
  }else if(x>Room[4][0] && y>Room[4][1] && x<Room[4][0]+1+Room[4][2] && y<Room[4][1]+1+Room[4][3]){   //5
    return 5;
  }else if(x>Room[3][0] && y>Room[3][1] && x<Room[3][0]+1+Room[3][2] && y<Room[3][1]+1+Room[3][3]){   //4
    return 4;
  }else if(x>Room[2][0] && y>Room[2][1] && x<Room[2][0]+1+Room[2][2] && y<Room[2][1]+1+Room[2][3]){   //3
    return 3;
  }else if(x>Room[1][0] && y>Room[1][1] && x<Room[1][0]+1+Room[1][2] && y<Room[1][1]+1+Room[1][3]){   //2
    return 2;
  }else if(x>Room[0][0] && y>Room[0][1] && x<Room[0][0]+1+Room[0][2] && y<Room[0][1]+1+Room[0][3]){   //1
    return 1;
  }
  else{                   //部屋にいない時
    return 0;
  }
  return 0;
}

/**　キャラクターのアクションを操作 **/
int CharctorController(charctor *charctor){
  HgWSetFillColor(charctorLayer,HG_RED);  //敵の場合赤色描画
  if(charctor->Exp != 0)   HgWSetFillColor(charctorLayer,HG_WHITE);  //自分の場合白色描画
  HgWCircleFill(charctorLayer,charctor->x*magnification-10,charctor->y*magnification-10,charctorSize,1);  //キャラクタを描画
  if(charctor->Exp != 0) {
    printf("player position : [%d][%d] , moveFlag : %d\n",charctor->x,charctor->y,charctor->moveFlag);
    if(charctor->Exp > tempExp*1.3){
      tempExp = charctor->Exp;  //前回の経験値を保持
      charctor->Lv++;
      MAXHP = (charctor->Lv*1.2)+10;
      charctor->attack++;
      charctor->defence++;
      strcpy(logStore,"レベルが上がった!!");
      logContoller(logStore);
      strcpy(logStore,"攻撃が１上がった");
      logContoller(logStore);
      strcpy(logStore,"防御が１上がった");
      logContoller(logStore);
    }
  }
  if(charctor->hp<0){
    if(charctor->Exp != 0){
      HgWSetFont(layerID,HG_G,150);
      HgWText(layerID,100,300,"GAME OVER");
    }
    else{
      terrian[charctor->x][charctor->y] = 1;
      charctor->x = -1;
      charctor->y = -1;
      charctor->ID = -1;
      charctor->hp=0;
      enemyCount--;
      player.Exp+=(80*level);
      snprintf(logStore,100,"敵を倒した!!経験値を%d得た",80*level);
      logContoller(logStore);
    }
  }

  return 0;
}

/** 部屋を取得
 **
 ** 各部屋を横幅８〜１２、縦８〜１０
 **  初期値 横幅１〜２、　縦１〜２でランダムに部屋を配置
**/
int getRoom(){
  int i,j,k,l,width,height,iniWid,iniHei,temp,X,Y;
  temp = 0;
  srand(time(NULL));
  for(i=0;i<3;i++){         //部屋の大きさを乱数で設定
    for(j=0;j<3;j++){       //部屋の大きさを乱数で設定
      iniHei = rand()%2+1;  //1から２まで部屋の初期いちをずらす
      iniWid = rand()%2+3;  //３から４まで部屋の初期いちをずらす
      width = rand()%4+8;   //8から12まで部屋の大きさを決定するX
      height = rand()%2+8;  //8から12まで部屋の大きさを決定するY

      X = iniWid+(j*18);    //Xの初期値
      Y = iniHei+(i*12);    //yの初期値

      for(l=Y;l<Y+height;l++){  //地形情報を保持
        for(k=X;k<X+width;k++){ //
          terrian[k][l] = 1;    //移動できる場所は1を代入
        }
      }

      HgWSetFillColor(layerID,HG_GREEN);  //部屋は緑色で描画
      HgWBoxFill(layerID,(X*magnification),(Y*magnification),width*magnification,height*magnification,1); //部屋を描画
      roomX[temp]=width;        //それぞれの部屋のXの大きさを保持
      roomY[temp]=height;       //それぞれの部屋のYの大きさを保持
      iniRoomX[temp] = iniWid;  //それぞれの部屋のずらした初期いちXの大きさを保持
      iniRoomY[temp] = iniHei;  //それぞれの部屋のずらした初期いちYの大きさを保持
      Room[temp][0] = X;
      Room[temp][1] = Y;
      Room[temp][2] = width;
      Room[temp][3] = height;

      temp++;
    }
  }
  return 0;
}

//道を取得
int getRoot(){
  int i;
  getRootRight(0,1);
  getRootRight(1,2);
  getRootRight(3,4);
  getRootRight(4,5);
  getRootRight(6,7);
  getRootRight(7,8);
  getRootUp(0,3);
  getRootUp(1,4);
  getRootUp(2,5);
  getRootUp(3,6);
  getRootUp(4,7);
  getRootUp(5,8);
  return 0;
}

/**
  * 部屋から部屋につなぐ道を計算、描画
  * first:左側,second:右側
  * 例: getRoomRight(0,1)...０番と１番の部屋で道をつなぐ
**/
int getRootRight(int first,int second){
  int i,rootFirst,rootSecond,height,leftX,leftY,leftWidth,rightX,rightY,rightWidth,rootToRootX;

  srand(time(NULL));
  rootFirst = rand()%(roomY[first]-1)+iniRoomY[first];    //ランダムで道の初期値を発生
  rootSecond = rand()%(roomY[second]-1)+iniRoomY[second]; //ランダムで道の初期値を発生
  height  = 1;                                            //道の幅
  rootToRootX = 16;                                       //道の基準点

  leftX       = (iniRoomX[first] + roomX[first]);         //Xの初期値(誤差と大きさを足した)
  leftY       = (1+rootFirst);                            //Yの初期値(初期値の１と乱数発生の値を足した)
  leftWidth   = (20-(3+iniRoomX[first]+roomX[first]));    //(全体からXの初期値を引いた)

  rightX      = 16;                                       //Xの基準点(基準点から出す値)
  rightY      = (rootSecond);                             //Yの基準点(基本の＋１と乱数発生の値を足した)
  rightWidth  = (2+iniRoomX[second]);                     //右の余分な１８と基準の３に乱数発生を足した)

  if(first%2!=0) {       //1-2,4-5,7-8の時は定数たす
    leftX+=18;
    rightX+=18;
    rootToRootX += 18;
  }
  if(first==3){          //4の時、上にずらさないといけないため、足し込み
    //デバッグ
    leftX-=18;
    rightX-=18;
    rootToRootX-=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;       //道と道をつなぐ際に必要な要素
    rootSecond+=12;      //上に同様
  }
  if(first==4){          //4の時、上にずらさないといけないため、足し込み
    //デバッグ
    leftX+=18;
    rightX+=18;
    rootToRootX+=18;

    leftY+=12;
    rightY+=12;
    rootFirst+=12;       //道と道をつなぐ際に必要な要素、
    rootSecond+=12;      //上に同様
  }
  if(first==6 || first==7){  //6,7の際に上にずらす必要がある
    leftY+=24;
    rightY+=24;
    rootFirst+=24;           //道と道をつなぐ際に必要な要素、
    rootSecond+=24;          //上に同様
  }
  Root[first][0][0]= leftX + 1;                               //道の位置を保持
  Root[first][0][1]= leftY + 1;                               //道の位置を保持
  Root[second][2][0] = rightX+rightWidth;                           //道の位置を保持
  Root[second][2][1] = rightY +1;                           //道の位置を保持
  //道は青
  HgWSetFillColor(layerID,HG_BLUE);
  //左から基準点までの道の描画
  HgWBoxFill(layerID,leftX*magnification,leftY*magnification,leftWidth*magnification,height*magnification,1);
  //右から基準点までの道の描画
  HgWBoxFill(layerID,rightX*magnification,rightY*magnification,rightWidth*magnification,height*magnification,1);

  //移動できる場所に2を代入
  for(i=leftX;i<leftX+leftWidth;i++){
    terrian[i][leftY] = 2;
  }
  //移動できる場所に2を代入　デバッグ
  if(rightWidth==4) rightX--;
  if(rightWidth == 6) rightWidth--;
  for(i=rightX-rightWidth;i<rightX+iniRoomX[second]-3;i++){
    terrian[5+i][rightY] = 2;
  }

  if (rootFirst != rootSecond){
    if(rootFirst>rootSecond){
      //道と道をつなぐ道は赤
      HgWSetFillColor(layerID,HG_RED);
      HgWBoxFill(layerID,                                       //道と道をつなぐ道の描画
                 rootToRootX*magnification,                     //左側が上にある時、基準点から道の高さまで描画する
                 rootSecond*magnification,
                 1*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,1);  //幅の絶対値をとる

      for(i=rootSecond;i<=rootSecond+abs(1+rootFirst-rootSecond);i++){
        terrian[rootToRootX][i] = 2;                            //移動できる場所に1を代入
      }
    }
    else{  //上に同様　
      HgWBoxFill(layerID,
                 rootToRootX*magnification,
                 (1+rootFirst)*magnification,
                 1*magnification,
                 abs(rootFirst-rootSecond)*magnification,1);

      for(i=rootFirst+1;i<=rootFirst+abs(rootFirst-rootSecond);i++){
        terrian[rootToRootX][i] = 2;  //移動できる場所に1を代入
      }
    }
  }
  return 0;
}

/** 縦の道をつなぐ、つなぎかたはgetRootRightに準ずる **/
int getRootUp(int first, int second){
  int i,rootFirst,rootSecond,height,lowX,lowY,lowHeight,highX,highY,highHeight,width,rootToRootY;
  srand(time(NULL));
  rootFirst = rand()%(roomX[first])+iniRoomX[first];    //誤差も含めたfirstの部屋のX座標方面大きさを決定,
  rootSecond = rand()%(roomX[second])+iniRoomX[second]; //誤差も含めたsecondの部屋のX座標方面の大きさを決定
  height = 12;
  width = 1;
  rootToRootY = 11;

  lowX       = (rootFirst);                             //Xの初期値(誤差と大きさを足す)
  lowY       = (roomY[first] +iniRoomY[first]);         //Yの初期値(初期値の１と乱数発生の値を足す)
  lowHeight   = (15-(3+iniRoomY[first]+roomY[first]));  //(全体からXの初期値を引いた)

  highX      = (rootSecond);                            //Xの基準点(基準点から出す値)
  highY      = 11;                                      //Yの基準点(基本の＋１と乱数発生の値を足した)
  highHeight  = (1+iniRoomY[second]);                   //右の余分な１８と基準の３に乱数発生を足した)

  if(first>2) {   //1-2,4-5,7-8の時は定数たす
    lowY+=12;
    highY+=12;
    rootToRootY += 12;
  }
  if(first==1 || first==4){  //getRootRightと同様
    lowX+=18;
    highX+=18;
    rootFirst+=18;           //道と道をつなぐ際に必要な要素、
    rootSecond+=18;          //上に同様
  }
  if(first==2 || first==5){  //getRootRightと同様
    lowX+=36;
    highX+=36;
    rootFirst+=36;           //道と道をつなぐ際に必要な要素、
    rootSecond+=36;          //上に同様
  }

  Root[first][1][0] = lowX+1;                           //道の位置を保持
  Root[first][1][1] = lowY+1;                           //道の位置を保持
  Root[second][3][0]=highX+1;                               //道の位置を保持
  Root[second][3][1]=highY+highHeight;                               //道の位置を保持

  //下から基準点までの道
  HgWSetFillColor(layerID,HG_RED);
  HgWBoxFill(layerID,lowX*magnification,lowY*magnification,width*magnification,lowHeight*magnification,1);

  for(i=lowY;i<lowHeight+lowY;i++){
    terrian[lowX][i] = 2;
  }
  //上から基準点までの道
  HgWSetFillColor(layerID,HG_GREEN);
  HgWBoxFill(layerID,highX*magnification,highY*magnification,width*magnification,highHeight*magnification,1);

  for(i=highY;i<highHeight+highY;i++){
    terrian[highX][i] = 2;
  }

  if(rootFirst==rootSecond || rootFirst+1==rootSecond || rootFirst-1==rootSecond){
    //printf("道を引く必要はありません。\n");
  }
  else{                             //道と道をつなぐ道の計算と描画
    if(rootFirst>rootSecond){
      HgWBoxFill(layerID,
                 rootSecond*magnification,
                 rootToRootY*magnification,
                 abs(1+rootFirst-rootSecond)*magnification,
                 1*magnification,1);
      for(i=rootSecond;i<rootSecond+abs(1+rootFirst-rootSecond);i++){
        terrian[i][rootToRootY] = 2;
      }
    }
    else{
      HgWBoxFill(layerID,
                 rootFirst*magnification,
                 rootToRootY*magnification,
                 abs(rootFirst-rootSecond)*magnification,
                 1*magnification,1);
      for(i=rootFirst;i<=rootFirst + abs(1+rootFirst-rootSecond);i++){
         terrian[i][rootToRootY] = 2;
       }
    }
  }
  return 0;
}

//位置調整
int regulation(){
  int i,j,temp;
  for(i=terrianSizeX;i>0;i--){
    for(j=terrianSizeY;j>0;j--){
      terrian[i+1][j+1] = terrian[i][j];
    }
  }
  return 0;
}

//地形生成をまとめた
int WriteTerrian(){
  int i,j,x,y;
    for(i=0;i<terrianSizeX;i++){
      for(j=0;j<terrianSizeY;j++){
          terrian[i][j] = 0;
      }
    }
    HgLClear(layerID);                       //ベースレイヤーをクリア
    getRoom();                               //部屋を取得
    getRoot();                               //道を取得
    regulation();                            //位置調整
    grid();                                  //グリッド線の描画
    enemyCount=1;
    for(i=1;i<6;i++){
      enemy[i].hp= 0;
      enemy[i].x= 0;
      enemy[i].y= 0;
      enemy[i].ID = 0;

    }

    while(1){
      srand(time(NULL));
      x = rand()%terrianSizeX;
      y = rand()%terrianSizeY;
      if(terrian[x][y]==1){
        terrian[x][y] = 8;
        stepX = x;
        stepY = y;
        x--;y--;
        HgWSetFillColor(layerID,HG_BLACK);
        HgWBoxFill(layerID,x*magnification,y*magnification,magnification,magnification,1);
        break;
      }
    }
    for(i=terrianSizeY-1;i>=0;i--){          //ログ
      for(j=0;j<terrianSizeX;j++){
        printf("%d ",terrian[j][i]);
      }
      printf("\n");
    }
    level++;
    snprintf(logStore,100,"階段を降りた%d階",level);
    logContoller(logStore);
  return 0;
}

//別ウィンドウのUIを操作
int UIController(){
  int hp = player.hp*10;
  int Lv = player.Lv;
  int damage = ((hp/MAXHP)+1)*10;
  int Exp = player.Exp;
  HgSetFont(HG_G,100);
  HgLClear(UILayer);
  HgWText(UILayer,10,70,"Lv : %d",Lv);
  HgWText(UILayer,10,50,"HP : %d/%d",hp/10,MAXHP);
  HgWSetFillColor(UILayer,HG_GREEN);
  HgWBoxFill(UILayer,10,30,100,20,1);
  HgWSetFillColor(UILayer,HG_RED);
  HgWBoxFill(UILayer,damage,30,110-damage,20,1);

  return 0;
}

//引数に取った番号にIDを設定して、敵を生成する
int AppearEnemy(int number){
  int x,y;
  srand(time(NULL));
  x=rand()%54;
  y = rand()%36;
  if(terrian[x][y]==1){
    enemy[number].x = x;
    enemy[number].y = y;
    enemy[number].hp = (rand()%11)+1+(level*1.3);
    enemy[number].Lv = rand()%20;
    enemy[number].Exp = 0;
    enemy[number].ID = number;
    enemy[number].attack = level;
    terrian[x][y]= 3;
    enemyCount++;
  }
  return number;
}

//キャラクターを右に移動
int moveRight(charctor *charctor){
  int x,y,state;
  x = charctor->x;
  y = charctor->y;
  state = terrian[charctor->x+1][charctor->y];
  if(terrian[charctor->x+1][charctor->y]==1 || terrian[charctor->x+1][charctor->y]==2 || terrian[charctor->x+1][charctor->y]==8) {
    if(charctor->Exp == 0){  //敵の移動
      if(terrian[charctor->x][charctor->y]==8)WriteTerrian();
      charctor->x++;
      terrian[x][y] = state;
      terrian[x+1][y] = 3;
    }
    else{                    //自身に移動
      charctor->x++;
      terrian[x][y] = state;
      terrian[x+1][y] = 9;
    }
    charctor->moveFlag = 0;
    return 1;
  }
  return 0;
}

//キャラクターを左に移動
int moveLeft(charctor *charctor){
  int x,y,state;
  x = charctor->x;
  y = charctor->y;
  state = terrian[charctor->x-1][charctor->y];
  if(terrian[(charctor->x)-1][charctor->y]==1 || terrian[(charctor->x)-1][charctor->y]==2 || terrian[charctor->x-1][charctor->y]==8) {
    if(charctor->Exp == 0){  //敵の移動
      if(terrian[charctor->x][charctor->y]==8)WriteTerrian();
      charctor->x-=1;
      terrian[x][y] = state;
      terrian[x-1][y] = 3;
    }
    else{
      charctor->x-=1;
      terrian[x][y] = state;
      terrian[x-1][y] = 9;
    }
    charctor->moveFlag = 2;
  }
  return 0;
}

//キャラクターを上に移動
int moveUp(charctor *charctor){
  int x,y,state;
  x = charctor->x;
  y = charctor->y;
  state = terrian[charctor->x][charctor->y+1];
  if(terrian[(charctor->x)][charctor->y+1]==1 || terrian[(charctor->x)][charctor->y+1]==2 || terrian[charctor->x][charctor->y+1]==8) {
    if(charctor->Exp == 0){  //敵の移動
      if(terrian[charctor->x][charctor->y]==8)WriteTerrian();
      charctor->y+=1;
      terrian[x][y] = state;
      terrian[x][y+1] = 3;
    }
    else{
      charctor->y+=1;
      terrian[x][y] = state;
      terrian[x][y+1] = 9;
    }
    charctor->moveFlag = 1;
  }
  return 0;
}

//キャラクターを下に移動
int moveDown(charctor *charctor){
  int x,y,state;
  x = charctor->x;
  y = charctor->y;
  state = terrian[charctor->x][charctor->y-1];
  if(terrian[(charctor->x)][charctor->y-1]==1 || terrian[(charctor->x)][charctor->y-1]==2 || terrian[charctor->x][charctor->y-1]==8) {
    if(charctor->Exp == 0){  //敵の移動
      if(terrian[charctor->x][charctor->y]==8)WriteTerrian();
      charctor->y-=1;
      terrian[x][y] = state;
      terrian[x][y-1] = 3;
    }
    else{
      charctor->y-=1;
      terrian[x][y] = state;
      terrian[x][y-1] = 9;
    }
    charctor->moveFlag = 3;
  }
  return 0 ;
}

//仮のグリッド線を描画
int grid(){
  int i,width,temp;
  temp = WindowWidth / terrianSizeX;
  for(i=0;i<terrianSizeX;i++){
    HgWLine(layerID,width,0,width,WindowHeight);
    HgWLine(layerID,0,width,WindowWidth,width);
    width = width + temp;
  }
  return 0;
}
