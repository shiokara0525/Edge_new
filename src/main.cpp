#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>
#include<ac.h>
#include<motor_a.h>


AC ac;
timer Timer;
int toogle_f;
int toogle_P = 27;
void Switch();
int LED = 13;
int count = 0;
motor_attack MOTOR;

void setup() {
  Serial.begin(9600);
  pinMode(toogle_P,INPUT);
  pinMode(LED,OUTPUT);
  ac.setup();
  Switch();
  Timer.reset();
}

void loop() {
  if(5000 < Timer.read_ms()){
    count++;
    if(count % 2 == 0){
      ac.dir_target += -90;
    }
    else if(count % 2 == 1){
      ac.dir_target += 90;
    }
    Timer.reset();
  }
  float AC_val = ac.getAC_val();
  MOTOR.motor_ac(AC_val);
  ac.print();
  Serial.println();
  delay(2);
  if(digitalRead(toogle_P) != toogle_f){
    MOTOR.motor_0();
    Switch();
  }
}


void Switch(){
  digitalWrite(LED,HIGH);
  toogle_f = digitalRead(toogle_P);
  delay(100);
  while(digitalRead(toogle_P) == toogle_f);
  digitalWrite(LED,LOW);
  ac.setup_2();
  toogle_f = digitalRead(toogle_P);
  delay(100);
  while(digitalRead(toogle_P) == toogle_f);
  toogle_f = digitalRead(toogle_P);
}