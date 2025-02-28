

#include "SparkFunLSM6DSO.h"
#include "Wire.h"
#include "FIR.h"
//#include "SPI.h"

LSM6DSO myIMU; //Default constructor is I2C, addr 0x6B

FIR firXG(5); //X gyro
FIR firYG(5); //Y gyro
FIR firZG(5); //Z gyro
FIR firXA(5); //X acelerometer
FIR firYA(5); //Y acelerometer
FIR firZA(5); //Z acelerometer

float XGyro;
float YGyro;
float ZGyro; 
float XAcel;
float YAcel;
float ZAcel;
void setup() {


  Serial.begin(115200);
  delay(500); 
  
  Wire.begin();
  delay(10);
  if( myIMU.begin() )
    Serial.println("Ready.");
  else { 
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
  }

  if( myIMU.initialize(BASIC_SETTINGS) )
    Serial.println("Loaded Settings.");

}


void loop()
{
  
  //Get all parameters
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X = ");
  //Serial.print(myIMU.readFloatAccelX(), 3);
  XAcel= firXA.updateOutput(myIMU.readFloatAccelX());
  Serial.println(XAcel);
  Serial.print(" Y = ");
 // Serial.print(myIMU.readFloatAccelY(), 3);
  
  YAcel= firYA.updateOutput(myIMU.readFloatAccelY());
  Serial.println(YAcel);
  Serial.print(" Z = ");
  //Serial.print(myIMU.readFloatAccelZ(), 3);
  ZAcel= firZA.updateOutput(myIMU.readFloatAccelZ());
  Serial.println(ZAcel);

  Serial.print("\nGyroscope:\n");
  Serial.print(" X = ");
  //Serial.println(myIMU.readFloatGyroX(), 3);
  XGyro= firXG.updateOutput(myIMU.readFloatGyroX());
  Serial.println(XGyro);
  Serial.print(" Y = ");
  //Serial.println(myIMU.readFloatGyroY(), 3);
  YGyro= firYG.updateOutput(myIMU.readFloatGyroY());
  Serial.println(YGyro);
  Serial.print(" Z = ");
  //Serial.println(myIMU.readFloatGyroZ(), 3);
  ZGyro= firZG.updateOutput(myIMU.readFloatGyroZ());
  Serial.println(ZGyro);

  
  delay(250);
}

