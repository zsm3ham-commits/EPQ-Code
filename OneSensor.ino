
#include <Wire.h>
#include <VL53L1X.h>
const uint8_t sensorCount = 2;
const uint8_t xshutPins[sensorCount] = {3, 5};
VL53L1X sensors[sensorCount];

void setup()
{
  while (!Serial) {}
  Serial.begin(9600 );
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect sensor!");
    while (1);
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
}

void loop()
{
  uint16_t distance = sensor.read();
  uint8_t status = sensor.ranging_data.range_status;

  if (status==0) {
    Serial.println(distance);
  }
  else{
    Serial.println("No object");
  }
  delay(100);
}
