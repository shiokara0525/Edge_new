#include<Cam.h>


Cam::Cam(int flag){
    csize.setLenth(20);
    csize.reset();
    if(flag == 3){
        F = 3;
        Serial3.begin(9600);
    }
    else if(flag == 4){
        F = 4;
        Serial4.begin(9600);
    }
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