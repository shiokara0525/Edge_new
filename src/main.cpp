#include <Arduino.h>

int PWM_p[5][2] = {
  {7,6},{2,3},{4,5},{8,9},{0,1}
};
int LED = 13;

void setup() {
  Serial.begin(9600);
  Serial8.begin(9600);
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