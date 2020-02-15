#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_LSM9DS1.h>
#include <TinyGPS++.h>

#define radioSerial Serial1
#define Gps_rx 4
#define Gps_tx 3

UART gpsSerial(digitalPinToPinName(Gps_rx), digitalPinToPinName(Gps_tx), NC, NC);
TinyGPSPlus gps;

struct radioPacket {
    byte start1 = 0x90;
    float Hts_temperature;
    float Bmp_pressure;
    float Imu_accelX;
    float Imu_accelY;
    float Imu_accelZ;
    float Imu_gyroX;
    float Imu_gyroY;
    float Imu_gyroZ;
    float Imu_magX;
    float Imu_magY;
    float Imu_magZ;
    float Gps_lat;
    float Gps_lng;
    uint32_t timestamp;
    byte end1 = 0xEB;
};

static radioPacket packet;

uint8_t packet_buf[sizeof(packet)];

void setup() {
  // put your setup code here, to run once:
  gpsSerial.begin(9600);
  radioSerial.begin(57600); //Serial port to radio
  //initialize IMU, barometer, temperature on ble
    while (!IMU.begin());
    while (!BARO.begin());
    while (!HTS.begin());
}

void loop() {
  

  packet.timestamp = millis();
  
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(packet.Imu_accelX, packet.Imu_accelY, packet.Imu_accelZ);
  }
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(packet.Imu_gyroX, packet.Imu_gyroY, packet.Imu_gyroZ);
  }
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(packet.Imu_magX, packet.Imu_magY, packet.Imu_magZ);
  }
  packet.Hts_temperature = HTS.readTemperature();
  packet.Bmp_pressure = BARO.readPressure();

  if (gpsSerial.available()){
    packet.Gps_lat = gps.location.lat();
    packet.Gps_lng = gps.location.lng();
  }
  
  memcpy(buffer, &packet, sizeof(packet));
  radioSerial.write((uint8_t *)&packet_buf, sizeof(packet_buf));

  delay(100);
  
}

