#pragma once

#include "RocketModule.h"

namespace Rocket {
#pragma pack(push, 1)
struct ROCKET_DATA {
    byte start1 = 0x90;

    float Bmp_altitude;
    float Hts_temperature;
    float Bmp_pressure;
    float Mpu_accelX;
    float Mpu_accelY;
    float Mpu_accelZ;
    float Mpu_gyroX;
    float Mpu_gyroY;
    float Mpu_gyroZ;
    float Mpu_magX;
    float Mpu_magY;
    float Mpu_magZ;
    float Gps_lat;
    float Gps_lng;
    uint32_t timestamp;
    byte crc;
    byte end1 = 0xEB;
};
#pragma pack(pop)
static ROCKET_DATA data;

const char *DATA_START = (char *)&data;
const int DATA_LEN = sizeof(ROCKET_DATA);

const int MODULE_NUM = 6;
const int Gps_ID = 0;
const int Bmp_ID = 1;
const int Mpu_ID = 2;
const int Hts_id = 3;
const int Radio_ID = 4;
const int SdCard_ID = 5;
}  // namespace Rocket

#include "Bmp.h"
#include "Gps.h"
#include "Mpu.h"
#include "Hts.h"
#include "Radio.h"
#include "SdCard.h"

#include "rocket_strings.h"

namespace Rocket {
static Bmp::Handler Bmp_INSTANCE;
static Gps::Handler Gps_INSTANCE;
static Mpu::Handler Mpu_INSTANCE;
static Hts::Handler Hts_INSTANCE;
static Radio::Handler Radio_INSTANCE;
static SdCard::Handler SdCard_INSTANCE;
static RocketModule *handlers[] = {&Bmp_INSTANCE, &Gps_INSTANCE, &Hts_INSTANCE,
                                   &Mpu_INSTANCE, &Radio_INSTANCE,
                                   &SdCard_INSTANCE};
}  // namespace Rocket
