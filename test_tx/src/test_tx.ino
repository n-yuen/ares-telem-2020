#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    while (!Serial){
        delay(1);
    }
    Serial.println("All set up");
    Serial1.begin(9600);


}

void loop(){
    Serial1.println("pee pee");
    delay(1000);
}