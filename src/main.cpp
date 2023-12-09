#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

const int C = 31;
const int K = 32;
const int LED = 13;


void setup() {
  pinMode(K,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(C,HIGH);
  digitalWrite(K,HIGH);
  digitalWrite(LED,HIGH);
}

void loop() {
  // digitalWrite(K,LOW);
  // digitalWrite(LED,LOW);
  // delay(5000);
  // digitalWrite(K,HIGH);
  // digitalWrite(LED,HIGH);
  // delay(1000);
  // digitalWrite(K,LOW);
  // digitalWrite(LED,LOW);
}