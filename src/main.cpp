#include <Arduino.h>

#define Pin 33
#define Pin_1 36
#define Pin_2 37
#define Pin_3 10
#define Pin_4 39
#define LED 13

void setup() {
  Serial.begin(9600);
  pinMode(Pin,OUTPUT);
  pinMode(Pin_1,OUTPUT);
  pinMode(Pin_2,OUTPUT);
  pinMode(Pin_3,OUTPUT);
  pinMode(Pin_4,OUTPUT);
  pinMode(LED,OUTPUT);
  analogWriteFrequency(Pin,60000);
  analogWrite(Pin,100);
  analogWrite(Pin_1,100);
  analogWrite(Pin_2,100);
  analogWrite(Pin_3,100);
  analogWrite(Pin_4,100);
  digitalWrite(LED,HIGH);
}



void loop() {
}