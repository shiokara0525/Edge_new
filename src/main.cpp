#include <Arduino.h>

#define Pin 33
#define LED 13

void setup() {
  Serial.begin(9600);
  pinMode(Pin,OUTPUT);
  pinMode(LED,OUTPUT);
  analogWriteFrequency(Pin,60000);
  analogWrite(Pin,100);
  digitalWrite(LED,HIGH);
}



void loop() {
}