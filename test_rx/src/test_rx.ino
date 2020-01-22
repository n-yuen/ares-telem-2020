#include <Arduino.h>
#include <SoftwareSerial.h>

void setup(){
    Serial.begin(9600);
    while (!Serial){
        delay(1);
    }

    Serial1.begin(57600);
    
}

void loop(){
    //int i;
    if (Serial1.available()){
        Serial.println( Serial1.readString());
        //Serial.println((int) i);
        //Serial.write(c);
    }
}