#include <Arduino.h>
#include<Cam.h>


void setup() {
  Serial4.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(0 < Serial4.available()){
    int A = Serial4.read();
    Serial.println(A);
  }
  else{
    Serial.println("sawA");
  }
  delay(100);
}