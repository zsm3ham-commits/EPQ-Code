#include <Wire.h>
#include <VL53L1X.h>

#define TCA_ADDR 0x70
#define NUM_SENSORS 8

VL53L1X sensor;

void tcaSelect(uint8_t bus)
{
  if (bus > 7) return;

  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << bus);
  Wire.endTransmission();
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  delay(100);

  for (uint8_t i = 0; i < NUM_SENSORS; i++)
  {
    tcaSelect(i);

    sensor.setTimeout(50);

    if (!sensor.init())
    {
      Serial.print("Sensor failed on channel ");
      Serial.println(i);
    }

    sensor.startContinuous(50);
  }

  Serial.println("VL53L1X setup complete");
}

void loop()
{
  for (uint8_t i = 0; i < NUM_SENSORS; i++)
  {
    tcaSelect(i);

    uint16_t distance = sensor.read();

    if (sensor.timeoutOccurred())
    {
      Serial.print("Timeout on channel ");
      Serial.println(i);
      delay(200);
    }
    else
    {
      Serial.print("Channel ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(distance);
      Serial.println(" mm");
    }
  }

  delay(1000);
}
