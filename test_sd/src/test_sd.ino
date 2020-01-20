// Feather9x_TX
// -*- mode: C++ -*-
//#include <RH_RF95.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SdFat.h>
#define DEBUG 1
#define FT_PER_M 0.304800609601
#define DELAY_INTERVAL 1000
#define SD_CHIPSEL 10

// Singleton instance of the radio driver
//RH_RF95 rf95(RFM95_CS, RFM95_INT);
#define gpsSerial Serial1


TinyGPSPlus gps;

SdFat sdCard;
SdBaseFile saveFile;


uint16_t highest_alt = 0;
long previousMillis = 0;


// curently 10 bytes, but we can reduce that if needed. Packet Num is unecesary.
// Just needed for testing.
struct gpsCoordinate {
    uint16_t lat;
    uint16_t lng;
} coord;


void printFormatted(uint16_t coordVal) {  // Prints decimal value
    uint32_t adjustedVal = (uint32_t)coordVal << 16;
    char toPrint[10];
    sprintf(toPrint, "%09lu", adjustedVal);  // Pad with zeroes
    toPrint[5] = '\0';                       // Truncate to 5 sigfigs
    Serial.print(toPrint);
}
uint8_t tx_buf[sizeof(coord)];
void setup() {

    Serial.println(sdCard.card()->errorCode());
    if(!sdCard.begin(SD_CHIPSEL)) {
        if(sdCard.card()->errorCode()) {
            Serial.print("Error code: ");
            Serial.println(sdCard.card()->errorCode(), HEX);
            Serial.println(sdCard.card()->errorData());
        }
        else {
            Serial.println("need a reformat");
        }
        return;
    }
    Serial.print("Trying to create file: ");
    if(saveFile.open("./output.txt", O_CREAT | O_WRITE | O_TRUNC)) {
        Serial.println("Created file");
        return;
    }
    else {
        Serial.println("Couldn't create the file");
        return;
    }
    Serial.println("all good");
//    pinMode(RFM95_RST, OUTPUT);
//    digitalWrite(RFM95_RST, HIGH);
    if (DEBUG) {
        Serial.begin(115200);
        // wait for usb serial, remove this line when not connected to pc
        while (!Serial) {
            delay(1);
        }
    }
    delay(100);
    Serial.println("yay");
    gpsSerial.begin(9600);

}

void loop() {
    int m;
    uint32_t lat, lng;
    //Serial.print("loop");
    if (gpsSerial.available()) {
        int x = gpsSerial.read();
        
        gps.encode(x);
        
        if (gps.location.isUpdated()) {
            
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis > DELAY_INTERVAL) {

                previousMillis = currentMillis;
                Serial.print("Lat = ");
                Serial.println(gps.location.lat(), 6);
                Serial.print("Lng = ");
                Serial.println(gps.location.lng(), 6);

                saveFile.write(gps.location.lat());
                saveFile.write(gps.location.lng());
            }
        }
    }
}
