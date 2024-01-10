#include <Arduino.h>
#include<motor_a.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>
#include<ac.h>
#include<ball.h>
#include<motor_a.h>

motor_attack motor;
void Switch();
int toogle_f;
int toogle_P = 27;
int LED = 13;


void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(toogle_P,INPUT);
  Switch();
}

void loop() {
  for(int i = 0; i < 4; i++){
    Serial.print(i);
    Serial.print(" ");
    motor.Moutput(i,100);
    delay(1000);
    motor.Moutput(i,0);
  }
  Serial.println();
  if(digitalRead(toogle_P) != toogle_f){
    Switch();
  }
}

void Switch(){
  digitalWrite(LED,HIGH);
  toogle_f = digitalRead(toogle_P);
  while(digitalRead(toogle_P) == toogle_f);
  digitalWrite(LED,LOW);
  toogle_f = digitalRead(toogle_P);
  delay(100);
  while(digitalRead(toogle_P) == toogle_f);
  toogle_f = digitalRead(toogle_P);
  Serial.println("ba-----ka");
}