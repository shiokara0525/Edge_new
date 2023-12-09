#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

const int C = 32;
const int K = 31;
const int LED = 13;

void kick();

void setup() {
  pinMode(K,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(C,HIGH);
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);
}

void loop() {
  delay(2000);
  kick();
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