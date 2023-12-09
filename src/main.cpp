#include <Arduino.h>
#include<Cam.h>
#include<ac.h>
#include<ball.h>
#include<line.h>
#include<motor_a.h>
#include<timer.h>

BALL ball;
int A = 0;
int val = 150;
AC ac;
int LED = 13;

motor_attack MOTOR;

LINE line;
int x = 0;
int y = 0;
int num = 0;

int line_A = 0;
int line_B = 999;
int Line_flag = 0;

const int ang_180 = 210;
const int ang_90 = 155;
const int ang_30 = 60;
const int ang_10 = 10;
int S_A = 0;
int S_B = 999;
timer S_t;
timer k_t;

int toogle_f;
int toogle_P = 27;

Cam cam_front(4);
Cam cam_back(3);
int AC_A;
int AC_B;
int AC_F;
int cam_flag = 0;
timer cam_T2;
float AC_ch();


const int C = 32;
const int K = 31;
void kick();

void setup() {
  Serial.begin(9600);
  Serial6.begin(57600);
  Serial8.begin(57600);
  ac.setup();

  pinMode(K,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(C,HIGH);
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);

  toogle_f = digitalRead(toogle_P);
  while(digitalRead(toogle_P) == toogle_f);
  ac.setup_2();
  toogle_f = digitalRead(toogle_P);
}



void loop() {
  angle go_ang(0,true);
  int AC_val = AC_ch();
  int go_val = val;

  if(A == 0){
    ball.getBallposition();
    line.getLINE_Vec(x,y,num);
    if(line.LINE_on){
      A = 20;
      line_A = 1;
    }
    else{
      A = 10;
      line_A = 0;
      if(line_A != line_B){
        if(Line_flag == 3){
          Serial.print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
          if((60 < abs(ball.ang) && abs(ball.ang) < 120) && (cam_front.Size < 15 || 50 < cam_back.Size)){
            A = 40;
          }
          else if((45 < abs(ball.ang) && abs(ball.ang) < 75) && cam_back.on == 0){
            A = 50;
            Serial.print("50!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
          }
        }
        line_B = line_A;
      }
      Line_flag = 0;
    }
  }

  if(A == 10){
    int ang_180_ = ang_180;
    int ang_90_ = ang_90;
    int ang_30_ = ang_30;
    int ang_10_ = ang_10;
    S_A = 0;

    if(AC_F == 1){
      ang_30_ = 135; 
    }
    if(abs(ball.ang) < 10){
      go_ang = ang_10 / 10.0 * ball.ang;
    }
    else if(abs(ball.ang) < 30){
      go_ang = ((ang_30_ - ang_10_) / 20.0 * (abs(ball.ang) - 10) + ang_10_)  * ball.ang / abs(ball.ang);
    }
    else if(abs(ball.ang) < 90){
      go_ang = ((ang_90_ - ang_30_) / 60.0 * (abs(ball.ang) - 30) + ang_30_) * ball.ang / abs(ball.ang);
    }
    else{
      go_ang = ((ang_180_ - ang_90_) / 90.0 * (abs(ball.ang) - 90) + ang_90_) * ball.ang / abs(ball.ang);
    }

    if(AC_A == 1){
      if(abs(ball.ang) < 10){
        go_ang = 0;
        S_A = 1;
      }
    }
    if(AC_F == 1){
      go_val = 120;
    }

    if(S_A == 0){
      if(S_A != S_B){
        S_B = S_A;
      }
    }
    else if(S_A == 1){
      if(S_A != S_B){
        S_B = S_A;
        S_t.reset();
      }
      if(200 < S_t.read_ms()){
        kick();
        S_t.reset();
        k_t.reset();
      }
    }
    A = 90;
  }



  if(A == 20){
    Serial.print(" sawa ");
    angle line_ang(line.ang,true);
    if(line_A != line_B){
      Line_flag = line.switchLineflag(line_ang);
      line_B = line_A;
    }
    go_ang = line.decideGoang(line_ang,Line_flag);
    // Serial.print("sawa");
    A = 90;
  }


  if(A == 40){
    while(30 < abs(ball.ang) && abs(ball.ang) < 150){
      ball.getBallposition();
      AC_val = ac.getAC_val();
      if(ball.ang < 0){
        go_ang = -90;
      }
      else{
        go_ang = 90;
      }
      ball.print();
      Serial.println(line.LINE_on);
      MOTOR.moveMotor_0(go_ang,go_val,AC_val,0);

      if(line.getLINE_Vec(x,y,num) == 1){
        break;
      }
    }
    A = 0;
    Serial.print(A);
    Serial.println("!!!!!!!!!!!!!!!!!!");
  }


  if(A == 50){
    Serial.print("50!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    while(45 < abs(ball.ang) && abs(ball.ang) < 75){
      ball.getBallposition();
      AC_val = ac.getAC_val();
      go_ang = 0;
      MOTOR.moveMotor_0(go_ang,go_val,AC_val,0);
      delay(500);
      if(line.getLINE_Vec(x,y,num) == 1){
        break;
      }
    }
    A = 0;
  }


  if(A == 90){
    MOTOR.moveMotor_0(go_ang,go_val,AC_val,0);

    // Serial.print(" ");
    // Serial.print(ball.ang);
    // Serial.print(" ");
    // Serial.print(go_ang.degree);
    // Serial.print(" ");
    // cam_front.print();
    // Serial.print(" ");
    // cam_back.print();
    // Serial.print(" ");
    // Serial.print(Line_flag);
    // Serial.print(go_val);
    // Serial.print(" ");
    // Serial.print(Line_flag);
    // line.print();
    // cam_front.print();
    ball.print();
    Serial.print(" ");
    cam_back.print();
    Serial.println();
    A = 0;
  }

  if(toogle_f != digitalRead(toogle_P)){
    Serial.print(" !!!!! ");
    MOTOR.motor_0();
    toogle_f = digitalRead(toogle_P);
    while(toogle_f == digitalRead(toogle_P));
    toogle_f = digitalRead(toogle_P);
    ac.setup_2();
    A = 0;
  }
}



float AC_ch(){
  float AC_val = 0;
  angle ball_(ball.ang + ac.dir,true);
  ball_.to_range(180,true);
  AC_A = 0;
  AC_F = 0;
  cam_flag = cam_front.on;

  if(cam_flag == 1){
    // Serial.print(" sawa ");
    if(AC_B == 1){
      if(abs(ball.ang) < 50 && abs(ball_.degree) < 60){
        AC_A = 1;
      }
    }
    else if(AC_B == 0){
      if(abs(ball.ang) < 20 && abs(ball_.degree) < 60){
        AC_A = 1;
      }
    }
  }

  if(AC_A == 0){
    if(AC_A != AC_B){
      AC_B = AC_A;
    }
    AC_val = ac.getAC_val();
  }
  else if(AC_A == 1){
    if(AC_A != AC_B){
      cam_T2.reset();
      AC_B = AC_A;
    }
    if(cam_T2.read_ms() < 200){
      AC_F = 1;
    }
    AC_val = ac.getCam_val(cam_front.ang);
  }
  return AC_val;
}


void kick(){
  digitalWrite(C,LOW);
  delay(100);
  digitalWrite(K,HIGH);
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);
  delay(100);
  digitalWrite(C,HIGH);
}


void serialEvent3(){
  uint8_t reBuf[4];
  if(Serial3.available() < 4){
    return;
  }

  for(int i = 0; i < 4; i++){
    reBuf[i] = Serial3.read();
    // Serial.print(reBuf[i]);
    // Serial.print(" ");
  }
  while(Serial3.available()){
    Serial3.read();
  }

  if(reBuf[0] == 38 && reBuf[3] == 37){
    if(reBuf[2] == 0){
      cam_back.on = 0;
    }
    else{
      cam_back.on = 1;
      cam_back.Size = reBuf[2];
      cam_back.ang = reBuf[1] - 127;
    }
  }
  // Serial.println("sawa");
}



void serialEvent4(){
  uint8_t reBuf[4];
  if(Serial4.available() < 4){
    return;
  }

  for(int i = 0; i < 4; i++){
    reBuf[i] = Serial4.read();
    // Serial.print(reBuf[i]);
    // Serial.print(" ");
  }
  while(Serial4.available()){
    Serial4.read();
  }

  if(reBuf[0] == 38 && reBuf[3] == 37){
    if(reBuf[2] == 0){
      cam_front.on = 0;
    }
    else{
      cam_front.on = 1;
      cam_front.Size = reBuf[2];
      cam_front.ang = -(reBuf[1] - 127);
    }
  }
  // Serial.println("sawa");
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
      Serial6.read();
    }
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
    // Serial.print(" x  : ");
    // Serial.print(x);
    // Serial.print(" y : ");
    // Serial.print(y);
    // Serial.print(" ang : ");
    // Serial.print(degrees(atan2(y,x)));
    // Serial.print(" | ");
  }
  else{
    // Serial.print(" Error!! ");
  }
  for(int i = 0; i < 7; i++){
    // Serial.print(read[i]);
    // Serial.print(" ");
  }
  // Serial.println();
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