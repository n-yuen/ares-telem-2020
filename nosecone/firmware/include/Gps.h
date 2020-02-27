#pragma once
#include "RocketModule.h"
///https://codeload.github.com/mikalhart/TinyGPSPlus/zip/master
#include <TinyGPS++.h>

#define RX_GPS 4
#define TX_GPS 3
#define GPS_BAUD 9600

namespace Gps{
    float &lat = Rocket::data.Gps_lat;
    float &lng = Rocket::data.Gps_lng;
    
    UART gpsSerial(digitalPinToPinName(RX_GPS), digitalPinToPinName(TX_GPS), NC, NC);

    class Handler: public Rocket::RocketModule {
    public:

        TinyGPSPlus gps;

        virtual bool warmup() {
            gpsSerial.begin(GPS_BAUD);
        }

        virtual void refresh() {
            
            if(!gpsSerial.available() || !gps.location.isUpdated() ) {
                return;
            }

            lat = gps.location.lat();
            lng = gps.location.lng();   
        }
    };
};