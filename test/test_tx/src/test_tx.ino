#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    while (!Serial){
        delay(1);
    }
    Serial.println("All set up");
    Serial1.begin(9600);
    if (Serial1){
        Serial.println(Serial1);
    }


}

void loop(){
    char msg[] = "pee pee";
    Serial.println(Serial1.print(msg));
    delay(1000);
    //kSerial.println("Message sent");
}