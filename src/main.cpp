#include<Arduino.h>

int motor = 6;//ESCに送る信号ピン
int volume = 100;//可変抵抗の値を入れる変数

void setup() {
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
}

void loop() {
  Serial.println(volume);//可変抵抗の値をシリアルモニタに表示
  analogWrite(motor, volume);//モータを動かす
  delay(100);
}
