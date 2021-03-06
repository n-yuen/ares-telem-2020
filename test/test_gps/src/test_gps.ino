#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <SPI.h>
#include <SD.h>
#include <Arduino_LSM9DS1.h>
#include <TinyGPS++.h>

#define DEBUG 1
#define FT_PER_M 0.304800609601
#define DELAY_INTERVAL 1000

#define SD_CHIPSEL 10
#define MOSI 11   //->DI
#define MISO 12   //->DO


#define gpsSerial Serial1

File myFile;

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
    if (DEBUG) {
        Serial.begin(9600);
        // wait for usb serial, remove this line when not connected to pc
        while (!Serial) {
            delay(1);
        }
    }
    delay(100);
    Serial.println("yay");
    gpsSerial.begin(9600);

    if (!IMU.begin()) {
      Serial.println("Failed to initialize IMU!");
      while (1);
    }
    if (!BARO.begin()) {
      Serial.println("Failed to initialize barometer!");
      while (1);
    }
    if (!HTS.begin()) {
      Serial.println("Failed to initialize temp sensor!");
      while (1);
    }

    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CHIPSEL)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");

    SD.remove("test.txt");
    SD.remove("testg.txt");
}

void loop() {
    int m;
    uint32_t lat, lng;
    if (gpsSerial.available()) {
        int x = gpsSerial.read();
        
        gps.encode(x);
        
        if (gps.location.isUpdated()) {
            unsigned long currentMillis = millis();
            
        myFile = SD.open("testg.txt", FILE_WRITE);
        // if the file opened okay, write to it:
        if (myFile) {
            Serial.println("Writing GPS data...");
            myFile.print("Lat = ");
            myFile.println(gps.location.lat(), 6);
            myFile.print("Lng = ");
            myFile.println(gps.location.lng(), 6);
          // close the file:
            myFile.close();
            Serial.println("done.");
            } 
            else {
            // if the file didn't open, print an error:
            Serial.println("error opening test.txt");
          }
        }

//READ IMU DATA
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
        
         myFile = SD.open("test.txt", FILE_WRITE);
         if (myFile) {
                  //Serial.print("Writing to test.txt...");
                  myFile.print("Accel = ");
                  myFile.print(ax);
                  myFile.print(ay);
                  myFile.println(az);
                  myFile.print("Gyro = ");
                  myFile.print(gx);
                  myFile.print(gy);
                  myFile.println(mz);
                  myFile.print("Mag = ");
                  myFile.print(mx);
                  myFile.print(my);
                  myFile.println(mz);
                  myFile.print("Temp = ");
                  myFile.println(temp);
                  myFile.print("Pressure = ");
                  myFile.println(pressure);
                // close the file:
                  myFile.close();
                  Serial.println("done.");
          } 
          else {
                  // if the file didn't open, print an error:
                  Serial.println("error opening test.txt");
          }
    }
}