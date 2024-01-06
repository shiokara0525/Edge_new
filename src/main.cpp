#include <Arduino.h>
#include<motor_a.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

motor_attack MOTOR;
int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  delay(400);
  digitalWrite(LED,LOW);
  delay(400);
  digitalWrite(LED,HIGH);
}

void loop() {
  for(int i = 0; i < 4; i++){
    MOTOR.Moutput(i,100);
    delay(500);
    MOTOR.motor_0();
  }
}