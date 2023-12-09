#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

const int C = 32;
const int K = 31;
const int LED = 13;


void setup() {
  pinMode(K,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(LED,OUTPUT);
  // digitalWrite(C,HIGH);
  // digitalWrite(K,HIGH);
  // digitalWrite(LED,HIGH);
}

void loop() {
  digitalWrite(C,HIGH);
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);
  delay(5000);
  digitalWrite(C,LOW);
  delay(500);
  digitalWrite(K,HIGH);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);
  delay(500);
}