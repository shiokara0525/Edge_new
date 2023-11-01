#include<Cam.h>


Cam::Cam(){
    Serial3.begin(9600);
    csize.setLenth(20);
    csize.reset();
}



void Cam::print(){
    if(on == 0){
        Serial.println("No block detected");
    }
    else{
        Serial.print("  ang: ");
        Serial.print(ang);
        Serial.print("  size: ");
        Serial.println(Size);
    }
}