#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

const int C = 35;
const int K = 33;
const int LED = 13;
#define DELAYVAL 500
#define PIN        30 
#define NUMPIXELS 16

Adafruit_NeoPixel pixels(DELAYVAL, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(K,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(LED,OUTPUT);
  pixels.begin();
  pixels.clear();
  digitalWrite(C,HIGH);
}

void loop() {
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);
  delay(5000);
  digitalWrite(K,HIGH);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(K,LOW);
  digitalWrite(LED,LOW);
}