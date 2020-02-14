///https://codeload.github.com/mikalhart/TinyGPSPlus/zip/master
#include <TinyGPS++.h>

#define RX_GPS 4
#define TX_GPS 3
#define GPS_BAUD 9600

namespace Gps{
    extern float lat;
    extern float lng;
    
    UART gpsSerial(digitalPinToPinName(RX_GPS), digitalPinToPinName(TX_GPS), NC, NC);

    class Handler: public Rocket::RocketModule {
    public:

        TinyGPSPlus gps;

        virtual bool warmup() {
            bool setupRight = gpsSerial.begin(GPS_BAUD);
            if(!setupRight) {
                return false;
            }

            return setupRight;
        }
        virtual void refresh() {
            
            if(!gps.available) {
                return;
            }

            lat = gps.location.lat();
            lng = gps.location.lng();   
        }
    }
}:
