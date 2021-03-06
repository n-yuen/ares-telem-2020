#pragma once

namespace Rocket {
	constexpr char* NAME_CSV = "Analog_CC,Analog_fuel,Analog_OX,Analog_press,Bmp_altitude,Bmp_temperature,Bmp_pressure,Mpu_accelX,Mpu_accelY,Mpu_accelZ,Mpu_gyroX,Mpu_gyroY,Mpu_gyroZ,Mpu_magX,Mpu_magY,Mpu_magZ,timestamp";
	constexpr char* TYPE_CSV = "uint16_t,uint16_t,uint16_t,uint16_t,float,float,float,float,float,float,float,float,float,float,float,float,uint32_t";
	constexpr char* MODULE_CSV = "Analog,Bmp,Mpu,Radio,SdCard";
	constexpr char* Gps_TEXT = "Gps";
	constexpr char* Bmp_TEXT = "Bmp";
	constexpr char* Mpu_TEXT = "Mpu";
	constexpr char* Radio_TEXT = "Radio";
	constexpr char* SdCard_TEXT = "SdCard";
	constexpr char* MODULE_NAMES[MODULE_NUM] = {
		Gps_TEXT,
		Bmp_TEXT,
		Mpu_TEXT,
		Radio_TEXT,
		SdCard_TEXT
	};
}
