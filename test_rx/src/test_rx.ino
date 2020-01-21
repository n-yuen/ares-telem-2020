#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    while (!Serial){
        delay(1);
    }

    Serial1.begin(9600);
    
}