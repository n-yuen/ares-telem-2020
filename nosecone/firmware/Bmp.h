#pragma once
#include "RocketModule.h"
#include <Arduino_LPS22HB.h>

namespace Bmp {
   // float &altitude = Rocket::data.Bmp_altitude;
   // float &temperature = Rocket::data.Bmp_temperature;
    float &pressure = Rocket::data.Bmp_pressure;

   // float seaLevel = 1013.25;

    class Handler: public Rocket::RocketModule {
    public:
      
        virtual bool warmup() {
            bool setupRight = BARO.begin();
            if(!setupRight) {
                return false;
            }
            return setupRight;
        }
        virtual void refresh() {
            pressure = BARO.readPressure();
        }
        virtual void shutdown(){
            BARO.end();
        }
    };
}
