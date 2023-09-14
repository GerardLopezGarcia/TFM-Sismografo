# TFM-Sismografo

link bueno : https://www.youtube.com/watch?v=UU5lcK7Tn8M&ab_channel=Alex7Tutoriales

Arduino Code : 

```
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
void setup() {
  Serial.begin(9600);  

  if(!accel.begin())
  {
    Serial.println("No ADXL345 sensor detected.");
    while(1);
  }

}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
  Serial.println("m/s^2 ");
  
  Serial.print(event.acceleration.x);
  Serial.print(" ");
  Serial.print(event.acceleration.y);
  Serial.print(" ");
  Serial.print(event.acceleration.z);
  Serial.println();
  delay(500);

}
```

