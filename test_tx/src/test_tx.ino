#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    while (!Serial){
        delay(1);
    }
    Serial.println("All set up");
    Serial1.begin(57600);


}

void loop(){
    char msg[] = "pee pee";
    Serial.println(Serial1.write("pee pee"));
    delay(1000);
    //kSerial.println("Message sent");
}