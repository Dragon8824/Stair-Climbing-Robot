//using the moving average example from FIR-Filter and the read distance sensor from VL531L1X

#include <Arduino.h>
#include "FIR.h"
#include <Wire.h>
#include "SparkFun_VL53L1X.h"
// create moving average FIR-Filter which averages over the last 5 inputs
FIR fir(5);
SFEVL53L1X distanceSensor;

void setup()
{
    Serial.begin(115200);

   if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
   {
     Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
     while (1)
      ;
    }
  Serial.println("Sensor online!");
}

void loop()
{
   distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }
  int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();

  Serial.print("Distance(mm): ");
  Serial.print(distance);
  

    // generate random values from analog pin
    float x;

    Serial.print(" Before: ");
    Serial.print(distance);

    // update filter
    x = fir.updateOutput(distance);
    
    Serial.print(" After:  ");
    Serial.println(x);
    Serial.println();

    delay(500);
}