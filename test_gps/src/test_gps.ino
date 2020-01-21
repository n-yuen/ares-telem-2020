#include <Arduino.h>

// Feather9x_TX
// -*- mode: C++ -*-
//#include <RH_RF95.h>
#include <SD.h>
#include <SPI.h>
#include <TinyGPS++.h>
//#include <SdFat.h>
#define DEBUG 1
#define FT_PER_M 0.304800609601
#define DELAY_INTERVAL 1000
#define SD_CHIPSEL 10
//#include <SoftwareSerial.h>

// Singleton instance of the radio driver
// RH_RF95 rf95(RFM95_CS, RFM95_INT);
#define gpsSerial Serial1

TinyGPSPlus gps;

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
    while (!Serial) {
        delay(1);
    }

    if (!SD.begin(SD_CHIPSEL)) {
        Serial.println("Failed");
    }
    Serial.print("Trying to create file: ");
    if (saveFile = SD.open("./output.txt", FILE_WRITE)) {
        Serial.println("Created file");
        return;
    } else {
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
    // Serial.print("loop");
    if (gpsSerial.available()) {
        int x = gpsSerial.read();

        gps.encode(x);

        if (gps.location.isUpdated()) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis > DELAY_INTERVAL) {
                previousMillis = currentMillis;
                float lat = gps.location.lat();
                float lng = gps.location.lng();
                Serial.print("Lat = ");
                Serial.println(lat, 6);
                Serial.print("Lng = ");
                Serial.println(lng, 6);
                char lats[7], lngs[7];
                sprintf(lats, "%7f", lat);
                sprintf(lngs, "%7f", lng);
                SD.write("(");
                SD.write(lats);
                SD.write(",");
                SD.write(lngs);
                SD.write(")");
                SD.flush();
                delay(1000);
            }
        }
    }
}