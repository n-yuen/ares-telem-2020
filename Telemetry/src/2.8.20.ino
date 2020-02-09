#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <SD.h>
#include <Arduino_LSM9DS1.h>
#include <TinyGPS++.h>


#define SD_CHIPSEL 10
#define radioSerial Serial1

UART gpsSerial(digitalPinToPinName(4), digitalPinToPinName(3), NC, NC);
TinyGPSPlus gps;
File myFile;

unsigned long t;
struct gpsCoordinate {
  uint16_t lat;
  uint16_t lng;
} coord;
int lat = 0;
int lng = 0;

void setup() {
  // put your setup code here, to run once:
  gpsSerial.begin(9600);
  radioSerial.begin(57600); //Serial port to radio
  //initialize IMU, barometer, temperature on ble
    while (!IMU.begin()) {
        IMU.begin();
    }
    while (!BARO.begin()) {
        BARO.begin();
    }
    while (!HTS.begin()) {
        HTS.begin();
    }

    //initialize sd card
    while (!SD.begin(SD_CHIPSEL)) {
        SD.begin(SD_CHIPSEL);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
//READ IMU DATA
  t = millis();
  float ax, ay, az, gx, gy, gz, mx, my, mz = 0;
  if (IMU.accelerationAvailable())  {
    IMU.readAcceleration(ax, ay, az);
  }
  if (IMU.gyroscopeAvailable()){
    IMU.readGyroscope(gx, gy, gz);
  }
  if (IMU.magneticFieldAvailable()){
    IMU.readMagneticField(mx, my, mz);
  }
  float temp = HTS.readTemperature();
  float pressure = BARO.readPressure();
//READ GPS
  if (gpsSerial.available()){
    lat = gps.location.lat();
    lng = gps.location.lng();
    /* Do you want to truncate these? */
  }
  else{
    lat = 0;
    lng = 0;
  }
  
//SEND
  if (lat != 0 && lng != 0){
    radioSerial.write(";");
    radioSerial.write(t);
    radioSerial.write(",");
    radioSerial.write(ax);
    radioSerial.write(ay);
    radioSerial.write(az);
    radioSerial.write(",");
    radioSerial.write(gx);
    radioSerial.write(gy);
    radioSerial.write(mz);
    radioSerial.write(",");
    radioSerial.write(mx);
    radioSerial.write(my);
    radioSerial.write(mz);
    radioSerial.write(",");
    radioSerial.write(temp);
    radioSerial.write(",");
    radioSerial.write(pressure);
    radioSerial.write(",");
    radioSerial.write(lat);
    radioSerial.write(",");
    radioSerial.write(lat);
  }
//WRITE TO SD
  myFile = SD.open("test.txt", FILE_WRITE);
  //HOW TO FORMAT THIS?
  if (myFile) {
          myFile.print(";");
          myFile.print(t);
          myFile.print(",");
          myFile.print(az);
          myFile.print(",");
          myFile.print(gx);
          myFile.print(gy);
          myFile.print(mz);
          myFile.print(",");
          myFile.print(mx);
          myFile.print(my);
          myFile.println(mz);
          myFile.print(",");
          myFile.print(temp);
          myFile.print(",");
          myFile.print(pressure);
          myFile.print(",");
          myFile.print(lat);
          myFile.print(",");
          myFile.println(lng);
        // close the file:
          myFile.close();
  }
}