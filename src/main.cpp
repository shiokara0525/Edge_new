#include<Arduino.h>

int toggle_p = 27;
int toggle_f = 0;
int LED = 13;

void setup(){
  pinMode(toggle_p,INPUT);
  pinMode(LED,OUTPUT);
}


void loop(){
  toggle_f = digitalRead(toggle_p);
  if(toggle_f == 1){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
}