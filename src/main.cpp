#include <Arduino.h>
#include<line.h>

LINE line;
int x = 0;
int y = 0;
int num = 0;
int A = 0;
int B = 999;
float go_ang;
int line_flag = 0;

void setup() {
  Serial.begin(9600);
  Serial6.begin(57600);
}

void loop() {
  go_ang = 0;
  line.getLINE_Vec(x,y,num);
  if(line.LINE_on){
    A = 1;
    angle line_dir(line.ang,true);
    if(A != B){
      B = A;
      line_flag = line.switchLineflag(line_dir);
    }
    go_ang = line.decideGoang(line_dir,line_flag);
  }
  else{
    A = 0;
    B = 0;
  }
  // line.print();
  Serial.print(go_ang);
  Serial.println();
}


void serialEvent6(){
  // Serial.print("sawa");
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
    // Serial.print("x : ");
    // Serial.print(x);
    // Serial.print(" y : ");
    // Serial.print(y);
    x *= -1;
    y *= -1;
  }
  else{
    // Serial.print(" Error!! ");
    // for(int i = 0; i < 7; i++){
    //   Serial.print(read[i]);
    //   Serial.print(" ");
    // }
  }

  Serial.println();
}