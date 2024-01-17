#include <Arduino.h>
#include<ball.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

#define DELAYVAL 500
#define PIN        30 
#define NUMPIXELS 16
BALL ball;
int ball_get;
int BtoN[16] = {12,11,10,9,8,7,6,5,4,3,2,1,0,15,14,13};

Adafruit_NeoPixel pixels(DELAYVAL, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ball.begin();
  Serial.begin(9600);
  pixels.begin();
  pixels.clear();
}

void loop() {
  // pixels.clear();
  ball.getBallposition();
  ball.print();
  int ball_ang = ball.ang + 180;
  int ball_flag;
  
  ball_flag = ball_ang / 22.5;
  Serial.print(" F : ");
  Serial.println(BtoN[ball_flag]);
  // pixels.setPixelColor(BtoN[ball_flag], pixels.Color(0, 150, 0));
  // pixels.show();
}



void serialEvent8(){
  int n;
  int x,y;
  word revBuf_word[7];
  byte revBuf_byte[7];
  // Serial.print("sawa");
  //受信データ数が、一定時間同じであれば、受信完了としてデータ読み出しを開始処理を開始する。
  //受信データあり ※6バイト以上になるまでまつ
  if(Serial8.available()>= 7){
    // Serial.print("ba-ka");
    //---------------------------
    //受信データをバッファに格納
    //---------------------------
    n = 0;
    while(Serial8.available()>0 ){ //受信データがなくなるまで読み続ける
      //6バイト目まではデータを格納、それ以上は不要なデータであるため捨てる。
      if(n < 7){
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
    if((revBuf_byte[0] == 0xFF ) && ( revBuf_byte[6] == 0xAA )){
    //いったんWORD型（16bitデータ）としてから、int16_tとする。
      revBuf_word[0] = (uint16_t(revBuf_byte[1])<< 8);//上位8ビットをbyteから、Wordに型変換して格納　上位桁にするため8ビットシフト
      revBuf_word[1] = uint16_t(revBuf_byte[2]);//下位8ビットをbyteから、Wordに型変換して格納      
      x = int16_t(revBuf_word[0]|revBuf_word[1]);//上位8ビット、下位ビットを合成（ビットのORを取ることで格納する。）
      // ※int ではなく　int16_t　にすることが必要。intだけだと、32ビットのintと解釈されマイナス値がマイナスとみなされなくなる、int16_tは、16ビット指定の整数型変換
      revBuf_word[2] = (uint16_t(revBuf_byte[3])<< 8);//上位8ビットをbyteから、Wordに型変換して格納　上位桁にするため8ビットシフト
      revBuf_word[3] = uint16_t(revBuf_byte[4]);//下位8ビットをbyteから、Wordに型変換して格納      
      y = int16_t(revBuf_word[2]|revBuf_word[3]);//上位8ビット、下位ビットを合成（ビットのORを取ることで格納する。）
      // ※int ではなく　int16_t　にすることが必要。intだけだと、32ビットのintと解釈されマイナス値がマイナスとみなされなくなる、int16_tは、16ビット指定の整数型変換
      ball_get = revBuf_byte[5];

      x = ball.ball_x.demandAve(x);
      y = ball.ball_y.demandAve(y);
      // Serial.print("!!");
      Serial.print(" x : ");
      Serial.print(x);
      Serial.print(" y : ");
      Serial.print(y);
      Serial.println();
    }
    else{
      printf("ERR_REV");
    }
  }
  else{
    Serial.print("ないよ");
  }
  // Serial.println("sawa");
  // int a = Serial8.read();
  // Serial.println(a);
}