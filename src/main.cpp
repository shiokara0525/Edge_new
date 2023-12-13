#include <Arduino.h>
#include <motor_a.h>

#define Pin 33
#define Pin_1 36
#define Pin_2 37
#define Pin_3 10
#define Pin_4 39
#define LED 13
motor_attack MOTOR;

void setup() {
  for(int i = 0; i < 5; i++){
    analogWriteFrequency(MOTOR.PWM_p[i][0],80000);
    MOTOR.Moutput(i,-250);
  }
}



void loop() {
}