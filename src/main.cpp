#include <Arduino.h>

int sawa[2] = {34,35};
int LED = 13;

void setup() {
  Serial.begin(9600);
  Serial8.begin(9600);
  for(int i = 0; i < 2; i++){
    pinMode(sawa[i],OUTPUT);
    digitalWrite(sawa[i],HIGH);
  }
}

void loop() {
  if(Serial8.available()){
    Serial.println("SAWA");
  }
}


void serialEvent8(){
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
  delay(500);
}