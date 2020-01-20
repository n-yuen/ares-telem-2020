// Feather9x_TX
// -*- mode: C++ -*-
//#include <RH_RF95.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SD.h>
#define DEBUG 1
#define FT_PER_M 0.304800609601
#define DELAY_INTERVAL 1000
#define SD_CHIPSEL 9

// Singleton instance of the radio driver
//RH_RF95 rf95(RFM95_CS, RFM95_INT);
// #define gpsSerial Serial1


TinyGPSPlus gps;

File saveFile;


uint16_t highest_alt = 0;
long previousMillis = 0;


// curently 10 bytes, but we can reduce that if needed. Packet Num is unecesary.
// Just needed for testing.
struct gpsCoordinate {
    uint16_t lat;
    uint16_t lng;
} coord;

uint8_t tx_buf[sizeof(coord)];
void setup() {

    Serial.begin(115200);

    if(!SD.begin(SD_CHIPSEL)) {
        Serial.println("Failed");
    }
    Serial.print("Trying to create file: ");
    if(saveFile = SD.open("./output.txt", FILE_WRITE)) {
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
    saveFile.write("1");
    saveFile.write("2");

    saveFile.close();

}

void loop() {

}
