
#include <Wire.h>
#include <VL53L1X.h>
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
