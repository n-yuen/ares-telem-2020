// Feather9x_TX
// -*- mode: C++ -*-
//#include <RH_RF95.h>
#include <SPI.h>
#include <TinyGPS++.h>
//#include <SdFat.h>
#define DEBUG 1
#define FT_PER_M 0.304800609601
#define DELAY_INTERVAL 1000
//#include <SoftwareSerial.h>

// Singleton instance of the radio driver
//RH_RF95 rf95(RFM95_CS, RFM95_INT);
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


void printFormatted(uint16_t coordVal) {  // Prints decimal value
    uint32_t adjustedVal = (uint32_t)coordVal << 16;
    char toPrint[10];
    sprintf(toPrint, "%09lu", adjustedVal);  // Pad with zeroes
    toPrint[5] = '\0';                       // Truncate to 5 sigfigs
    Serial.print(toPrint);
}
uint8_t tx_buf[sizeof(coord)];
void setup() {
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
            }
        }
    }
}