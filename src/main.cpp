#include <Arduino.h>
#include<Cam.h>
#include<ac.h>

AC ac;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.print("sawa");
  ac.setup();
  Serial.print("aho");
}

void loop() {
  Serial.println(ac.getAC_val());
  delay(50);
}