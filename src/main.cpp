#include <Arduino.h>
#include<line.h>

LINE line;
int x = 0;
int y = 0;
int num = 0;

void setup() {
  Serial.begin(9600);
  Serial6.begin(57600);
}

void loop() {
  line.getLINE_Vec(x,y,num);
  line.print();
  Serial.println();
}


void serialEvent6(){
  delayMicroseconds(100);
  uint8_t read[7];
  word contain[4];
  int n = 0;
  if(Serial6.available() < 7){
    return;
  }
  while(0 < Serial6.available()){
    if(n < 7){
      read[n] = Serial6.read();
    }
    else{
      Serial6.read();
    }
    n++;
  }

  if(read[0] == 38 && read[6] == 37){
    contain[0] = (uint16_t(read[1]) << 8);
    contain[1] = (uint16_t(read[2]));
    x = int16_t(contain[0] | contain[1]);
    contain[2] = (uint16_t(read[3]) << 8);
    contain[3] = (uint16_t(read[4]));
    y = int16_t(contain[2] | contain[3]);
    num = read[5];
    Serial.print("x : ");
    Serial.print(x);
    Serial.print(" y : ");
    Serial.print(y);
  }
  else{
    Serial.print(" Error!! ");
    for(int i = 0; i < 7; i++){
      Serial.print(read[i]);
      Serial.print(" ");
    }
  }

  Serial.println();
}