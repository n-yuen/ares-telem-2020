#pragma once
#include "RocketModule.h"
#include <Arduino_HTS221.h>

namespace Hts {
    float &temperature = Rocket::data.Bmp_temperature;
    
    class Handler: public Rocket::RocketModule {
    public:
        virtual bool warmup() {
            bool setupRight = HTS.begin();
            if(!setupRight) {
                return false;
            }
            return setupRight;
        }
        virtual void refresh() {
            pressure = HTS.readTemperature();
        }
        virtual void shutdown(){
            HTS.end();
        }
    };
}
