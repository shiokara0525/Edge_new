#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

#define DELAYVAL 500
#define PIN        30 
#define NUMPIXELS 16


int A = 1;
int val = 100;
int PWM_p[5][2] = {
  {7,6},{2,3},{4,5},{8,9},{0,1}
};
int LED = 13;
void motor(float ang);

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 5; i++){
    pinMode(PWM_p[i][0],OUTPUT);
    pinMode(PWM_p[i][1],OUTPUT);
  }
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  delay(400);
  digitalWrite(LED,LOW);
  delay(400);
  digitalWrite(LED,HIGH);
}

void loop() {
  motor(45);
}



void motor(float ang){
  double mSin[4] = {1,1,-1,-1};  //行列式のsinの値
  double mCos[4] = {1,-1,-1,1};  //行列式のcosの値
  float X = cos(radians(ang));
  float Y = sin(radians(ang));
  float A = 0;
  float B = 0;
  float Mval[4];
  double g = 0;                //モーターの最終的に出る最終的な値の比の基準になる値
  for(int i = 0; i < 4; i++){
    A = -mSin[i] * X;
    B = mCos[i] * Y;
    Mval[i] = A + B; //モーターの回転速度を計算(行列式で管理)
    if(i == 0){
      Serial.print(" |  ");
      Serial.print(A);
      Serial.print(" ");
      Serial.print(B);
      Serial.print("  | ");
    }
    Serial.print(" ");
    Serial.print(Mval[i]);
    if(abs(Mval[i]) > g){  //絶対値が一番高い値だったら
      g = abs(Mval[i]);    //一番大きい値を代入
    }
  }

  for(int i = 0; i < 4; i++){
    Mval[i] = Mval[i] / g * val;  //モーターの値を計算(進みたいベクトルの値と姿勢制御の値を合わせる)
    if(Mval[i] < 0){
      analogWrite(PWM_p[i][0],abs(Mval[i]));
      analogWrite(PWM_p[i][1],0);
    }
    else if(0 < Mval[i]){
      analogWrite(PWM_p[i][0],0);
      analogWrite(PWM_p[i][1],abs(Mval[i]));
    }

  }
  Serial.println();
}