#include <Arduino.h>
#include<ac.h>
#include<ball.h>
#include<line.h>

BALL ball;
int A = 1;
int val = 200;
int PWM_p[5][2] = {
  {7,6},{2,3},{5,4},{8,9},{0,1}
};
AC ac;
int LED = 13;
void motor(float ang,float ac_v);
float X = 0;
float Y = 0;

LINE line;
int x = 0;
int y = 0;
int num = 0;

int line_A = 0;
int line_B = 999;
int Line_flag = 0;


void setup() {
  Serial.begin(9600);
  Serial6.begin(57600);
  Serial8.begin(57600);
  for(int i = 0; i < 5; i++){
    pinMode(PWM_p[i][0],OUTPUT);
    pinMode(PWM_p[i][1],OUTPUT);
  }
  ac.setup();
  Serial.println("sawa");
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  delay(400);
  digitalWrite(LED,LOW);
  delay(400);
  digitalWrite(LED,HIGH);
}

void loop() {
  angle go_ang(0,true);
  ball.getBallposition();
  line.getLINE_Vec(x,y,num);

  float AC_val = ac.getAC_val();

  if(line.LINE_on == 1){
    angle line_ang(line.ang,true);
    if(line_A != line_B){
      Line_flag = line.switchLineflag(line_ang);
      line_B = line_A;
      go_ang = line.decideGoang(line_ang,Line_flag);
    }
    go_ang = line.decideGoang(line_ang,Line_flag);
  }

  // motor(go_ang.degree,AC_val);
  // line.print();
}



void motor(float ang,float ac_v){
  double mSin[4] = {1,1,-1,-1};  //行列式のsinの値
  double mCos[4] = {1,-1,-1,1};  //行列式のcosの値
  float X = cos(radians(ang));
  float Y = sin(radians(ang));
  float Mval[4];
  double g = 0;                //モーターの最終的に出る最終的な値の比の基準になる値
  float val_ = val;
  val_ -= ac_v;

  for(int i = 0; i < 4; i++){
    Mval[i] = -mSin[i] * X + mCos[i] * Y; //モーターの回転速度を計算(行列式で管理)
    if(abs(Mval[i]) > g){  //絶対値が一番高い値だったら
      g = abs(Mval[i]);    //一番大きい値を代入
    }
  }

  for(int i = 0; i < 4; i++){
    Mval[i] = Mval[i] / g * val_ + ac_v;  //モーターの値を計算(進みたいベクトルの値と姿勢制御の値を合わせる)
    if(Mval[i] < 0){
      analogWrite(PWM_p[i][0],abs(Mval[i]));
      analogWrite(PWM_p[i][1],0);
    }
    else if(0 < Mval[i]){
      analogWrite(PWM_p[i][0],0);
      analogWrite(PWM_p[i][1],abs(Mval[i]));
    }
    Serial.print(Mval[i]);
    Serial.print(" ");
  }
}



void serialEvent6(){
  // Serial.print("sawa");
  uint8_t read[7];
  word contain[4];
  int n = 1;
  if(Serial6.available() < 7){
    return;
  }
  read[0] = Serial6.read();
  if(read[0] != 38){
    return;
  } 
  while(0 < Serial6.available()){
    if(n < 7){
      read[n] = Serial6.read();
    }
    else{
    else{
      Serial6.read();
    }
    n++;
    n++;
  }

  if(read[0] == 38 && read[6] == 37){
    contain[0] = (uint16_t(read[1]) << 8);
    contain[1] = (uint16_t(read[2]));
    x = int16_t(contain[0] | contain[1]);
    contain[2] = (uint16_t(read[3]) << 8);
    contain[3] = (uint16_t(read[4]));
    y = int16_t(contain[2] | contain[3]);
    num = read[5];
    x *= -1;
    y *= -1;
    Serial.print(" x  : ");
    Serial.print(x);
    Serial.print(" y : ");
    Serial.print(y);
    Serial.print(" ang : ");
    Serial.print(degrees(atan2(y,x)));
    Serial.print(" | ");
  }
  else{
    Serial.print(" Error!! ");
  }
  for(int i = 0; i < 7; i++){
    Serial.print(read[i]);
    Serial.print(" ");
  }
  Serial.println();
}




void serialEvent8(){
  int n;
  int x,y;
  word revBuf_word[6];
  byte revBuf_byte[6];
  //受信データ数が、一定時間同じであれば、受信完了としてデータ読み出しを開始処理を開始する。
  //受信データあり ※6バイト以上になるまでまつ
  if(Serial8.available()>= 6){
    //---------------------------
    //受信データをバッファに格納
    //---------------------------
    n = 0;
    while(Serial8.available()>0 ){ //受信データがなくなるまで読み続ける
      //6バイト目まではデータを格納、それ以上は不要なデータであるため捨てる。
      if(n < 6){
        revBuf_byte[n] = Serial8.read();   //revBuf_byte[n] = Serial2.read();
      }
      else{
        Serial8.read(); //Serial2.read();  //読みだすのみで格納しない。
      }
      n++;
    }
    //---------------------------
    //データの中身を確認
    //---------------------------
    //データの先頭、終了コードあることを確認
    if((revBuf_byte[0] == 0xFF ) && ( revBuf_byte[5] == 0xAA )){
    //いったんWORD型（16bitデータ）としてから、int16_tとする。
      revBuf_word[0] = (uint16_t(revBuf_byte[1])<< 8);//上位8ビットをbyteから、Wordに型変換して格納　上位桁にするため8ビットシフト
      revBuf_word[1] = uint16_t(revBuf_byte[2]);//下位8ビットをbyteから、Wordに型変換して格納      
      x = int16_t(revBuf_word[0]|revBuf_word[1]);//上位8ビット、下位ビットを合成（ビットのORを取ることで格納する。）
      // ※int ではなく　int16_t　にすることが必要。intだけだと、32ビットのintと解釈されマイナス値がマイナスとみなされなくなる、int16_tは、16ビット指定の整数型変換
      revBuf_word[2] = (uint16_t(revBuf_byte[3])<< 8);//上位8ビットをbyteから、Wordに型変換して格納　上位桁にするため8ビットシフト
      revBuf_word[3] = uint16_t(revBuf_byte[4]);//下位8ビットをbyteから、Wordに型変換して格納      
      y = int16_t(revBuf_word[2]|revBuf_word[3]);//上位8ビット、下位ビットを合成（ビットのORを取ることで格納する。）
      // ※int ではなく　int16_t　にすることが必要。intだけだと、32ビットのintと解釈されマイナス値がマイナスとみなされなくなる、int16_tは、16ビット指定の整数型変換
      
      x = ball.ball_x.demandAve(x);
      y = ball.ball_y.demandAve(y);
    }
    else{
      // printf("ERR_REV");
    }
  }
  // Serial.println("sawa");
  // int a = Serial8.read();
  // Serial.println(a);
}