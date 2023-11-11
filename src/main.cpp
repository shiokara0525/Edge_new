#include <Arduino.h>
#include<Adafruit_NeoPixel.h>
#include<Cam.h>

const int C = 35;
const int K = 33;
const int LED = 13;
#define DELAYVAL 500
#define PIN        30 
#define NUMPIXELS 16

Adafruit_NeoPixel pixels(DELAYVAL, PIN, NEO_GRB + NEO_KHZ800);

int x = 0;
int y = 0;
int num = 0;

void setup() {
  Serial.begin(9600);
  Serial6.begin(9600);
  pixels.begin();
}

void loop() {
}


void serialEvent6(){
  uint8_t read[7];
  if(7 <= Serial6.available()){
    for(int i = 0; i < 5; i++){
      read[i] = Serial6.read();
    }
    while(Serial6.available()){
      Serial6.read();
    }
  }

  if(read[0] == 38 && read[4] == 37){
    x = read[1];
    y = read[2];
    num = read[3];
  }
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.println(num);
}