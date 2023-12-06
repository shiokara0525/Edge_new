#include <Arduino.h>
#include<Cam.h>
#include<ac.h>

Cam cam_front(4);
Cam cam_back(3);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.print("sawa");
  Serial.print("aho");
}

void loop() {
  delay(2);
  cam_front.print();
}


void serialEvent3(){
  uint8_t reBuf[4];
  if(Serial3.available() < 4){
    return;
  }

  for(int i = 0; i < 4; i++){
    reBuf[i] = Serial3.read();
    // Serial.print(reBuf[i]);
    // Serial.print(" ");
  }
  while(Serial3.available()){
    Serial3.read();
  }

  if(reBuf[0] == 38 && reBuf[3] == 37){
    if(reBuf[2] == 0){
      cam_back.on = 0;
    }
    else{
      cam_back.on = 1;
      cam_back.Size = reBuf[2];
      cam_back.ang = reBuf[1] - 127;
    }
  }
  Serial.println("sawa");
}



void serialEvent4(){
  uint8_t reBuf[4];
  if(Serial4.available() < 4){
    return;
  }

  for(int i = 0; i < 4; i++){
    reBuf[i] = Serial4.read();
    // Serial.print(reBuf[i]);
    // Serial.print(" ");
  }
  while(Serial4.available()){
    Serial4.read();
  }

  if(reBuf[0] == 38 && reBuf[3] == 37){
    if(reBuf[2] == 0){
      cam_front.on = 0;
    }
    else{
      cam_front.on = 1;
      cam_front.Size = reBuf[2];
      cam_front.ang = reBuf[1] - 127;
    }
  }
  Serial.println("sawa");
}