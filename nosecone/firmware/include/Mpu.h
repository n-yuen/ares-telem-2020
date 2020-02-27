#pragma once
#include "RocketModule.h"
///https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library/archive/master.zip
#include <Arduino_LSM9DS1.h>
#include <Wire.h>

/*
 * an IIFE that gives the average of a 100 readings
 * M is the name of the method (calcAccel/calcGyro)
 * V is the name of the variable (ax/gx)
*/
// #define AVG_100(M, V) \
//     [&] { \
//     float total = 0; \
//     for(int i = 0; i < 100; i++) { \
//         IMU.update(UPDATE_ACCEL | UPDATE_GYRO | UPDATE_COMPASS); \
//         total+= IMU.M(IMU.V); \
//     } \
//     return total / 100; \
// }();

namespace Mpu {
    float &accelX = Rocket::data.Mpu_accelX;
    float &accelY = Rocket::data.Mpu_accelY;
    float &accelZ = Rocket::data.Mpu_accelZ;
    float &gyroX = Rocket::data.Mpu_gyroX;
    float &gyroY = Rocket::data.Mpu_gyroY;
    float &gyroZ = Rocket::data.Mpu_gyroZ;
    float &magX = Rocket::data.Mpu_magX;
    float &magY = Rocket::data.Mpu_magY;
    float &magZ = Rocket::data.Mpu_magZ;
    float ax, ay, az, gx, gy, gz, mx, my, mz;

    struct CalibData {
        float offsets[6];
        float scales[3];
    };

    //FlashStorage(calibData, CalibData);
    
    class Handler: public Rocket::RocketModule {
    public:
        float *offsetVals;
        float *scaleVals;
        CalibData calib;
        virtual bool warmup() {
            bool setupRight = (IMU.begin());
            if(!setupRight) {
                return false;
            }

            // calib = calibData.read();

            // offsetVals = calib.offsets;
            // scaleVals = calib.scales;
            // //make sure none of the scales are 0
            // for(int i = 0; i < 3; i++) {
            //     if(scaleVals[i] == 0) {
            //         scaleVals[i] = 1;
            //     }
            // }

            return setupRight;
        }
        virtual void refresh() {
            //SerialUSB.println(Rocket::data.Mpu_accelX);
            if (IMU.gyroscopeAvailable())   IMU.readAcceleration(ax, ay, az);
            accelX = ax;
            accelY = ay;
            accelZ = az;

            if (IMU.accelerationAvailable())   IMU.readGyroscope(gx, gy, gz);
            gyroX = gx;
            gyroY = gy;
            gyroZ = gz;

            if (IMU.magneticFieldAvailable())     IMU.readMagneticField(mx, my, mz);
            magX = mx;
            magY = my;
            magZ = mz;
            
            // accelX = (IMU.calcAccel(IMU.ax) - offsetVals[0]) * scaleVals[0]; // accelX is x-axis acceleration in g's
            // accelY = (IMU.calcAccel(IMU.ay) - offsetVals[1]) * scaleVals[1]; // accelY is y-axis acceleration in g's
            // accelZ = (IMU.calcAccel(IMU.ay) - offsetVals[2]) * scaleVals[2]; // accelZ is z-axis acceleration in g's

            // gyroX = (IMU.calcGyro(IMU.gx) - offsetVals[3]); // gyroX is x-axis rotation in dps
            // gyroY = (IMU.calcGyro(IMU.gy) - offsetVals[4]); // gyroY is y-axis rotation in dps
            // gyroZ = (IMU.calcGyro(IMU.gz) - offsetVals[5]); // gyroZ is z-axis rotation in dps
            
            // magX = IMU.calcMag(IMU.mx); // magX is x-axis magnetic field in uT
            // magY = IMU.calcMag(IMU.my); // magY is y-axis magnetic field in uT
            // magZ = IMU.calcMag(IMU.mz); // magZ is z-axis magnetic field in uTcc
        }
        // float readSensor(int id) {
        //     SerialUSB.println("Reading sensor ");
        //     float f = 0;
        //     if(id == 0) {
        //         f = AVG_100(calcAccel, ax)
        //     }
        //     else if(id == 1) {
        //         f = AVG_100(calcAccel, ay)
        //     }
        //     else if(id == 2) {
        //         f = AVG_100(calcAccel, az)
        //     }
        //     else if(id == 3) {
        //         f = AVG_100(calcGyro, gx)
        //     }
        //     else if(id == 4) {
        //         f = AVG_100(calcGyro, gy)
        //     }
        //     else if(id == 5) {
        //         f = AVG_100(calcGyro, gz)
        //     }
        //     SerialUSB.println(f);
        //     return f;
        // }
        // virtual void calibrate() {
        //     SerialUSB.println("Calibrating the MPU. Press enter when you're done with the instruction");            
        //     const char *sensorOrder[] = {
        //         "accelX",
        //         "accelY",
        //         "accelZ",
        //         "gyroX",
        //         "gyroY",
        //         "gyroZ"
        //     };

        //     for(int i = 0; i < 6; i++) {
        //         SerialUSB.print("Null ");
        //         SerialUSB.println(sensorOrder[i]);
                
        //         while(SerialUSB.available() == 0);
        //         SerialUSB.read();

        //         float offset = readSensor(i);
        //         offsetVals[i] = offset;

        //         if(i >= 3) {
        //             continue; //no maxIMUms for the gyroscopes
        //         }

        //         SerialUSB.print("Max ");
        //         SerialUSB.println(sensorOrder[i]);
                
        //         while(SerialUSB.available() == 0);
        //         SerialUSB.read();

        //         float high = readSensor(i);
        //         float delta = high - offset;
        //         //let's avoid db0
        //         if(delta == 0) {
        //             scaleVals[i] = 1;
        //         }
        //         else {
        //             scaleVals[i] = 1 / delta;
        //         }
        //     }
        //     calibData.write(calib);
        //     SerialUSB.println("Calibration complete");
        // }
    };
}
// #undef AVG_100