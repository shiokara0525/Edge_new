#include <Arduino.h>
#include<motor_a.h>
motor_attack MOTOR;
#define pin 2
#define LED 13

void setup(){
  analogWriteFrequency(pin,90000);
  pinMode(pin,OUTPUT);
  digitalWrite(LED,HIGH);
}

void loop(){
  MOTOR.Moutput(3,200);
  delay(500);
  MOTOR.Moutput(3,-200);
  delay(500);
}