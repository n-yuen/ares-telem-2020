#include <Arduino.h>

void setup(){
    Serial.begin(9600);
    while (!Serial){
        delay(1);
    }

    Serial1.begin(9600);
    while (!Serial1){
        delay(1);
    }
    Serial.println(Serial1);
    
}

void loop(){
    //int i;
    // if (Serial1.available()){
    //     Serial.println(Serial1.readString());
    //     //Serial.println((int) i);
    //     //Serial.write(c);
    // }
    Serial1.write(Serial.read());
}