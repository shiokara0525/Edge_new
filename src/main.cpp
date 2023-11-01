#include <Arduino.h>
#include<Cam.h>
#include<ac.h>

Cam cam;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.print("sawa");
  Serial.print("aho");
}

void loop() {
  delay(100);
  cam.print();
}


void serialEvent3(){
  uint8_t reBuf[4];
  if(4 < Serial3.available()){
    for(int i = 0; i < 4; i++){
      reBuf[i] = Serial3.read();
      // Serial.print(reBuf[i]);
      // Serial.print(" ");
    }
  }
  else{
    reBuf[0] = Serial3.read();
    // Serial.print(reBuf[0]);
    // Serial.print(" ");
  }

  if(reBuf[0] == 38 && reBuf[3] == 37){
    if(reBuf[2] == 0){
      cam.on = 0;
    }
    else{
      cam.on = 1;
      cam.Size = reBuf[2];
      cam.ang = reBuf[1] - 30;
    }
  }
  Serial.println("sawa");
}