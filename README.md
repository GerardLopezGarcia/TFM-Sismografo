# TFM-Sismografo
![image](https://github.com/GerardLopezGarcia/TFM-Sismografo/assets/72072309/5307ff06-9d18-416b-89cb-6652d85d11a2)


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

AHORA EL DE VERDAD

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
#include <ezButton.h>
#define LOOP_STATE_STOPPED 0
#define LOOP_STATE_STARTED 1
ezButton button(A3);
int loopState = LOOP_STATE_STOPPED;

const int analogInPin = A1;

int sensorValue = 0;
int outputValue = 0;
int llistaDeValors[100];

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

bool triggerActivated = false;

unsigned long previousMicros = 0;
const unsigned long interval = 500000;

void saveData(unsigned long currentMicros, int sensorValue) {
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Value : " + (String) sensorValue);
}

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(50);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing...");
}

void loop() {
  button.loop();
  
  if (button.isPressed()) {
    if (loopState == LOOP_STATE_STOPPED)
      loopState = LOOP_STATE_STARTED;
    else 
      loopState = LOOP_STATE_STOPPED;
  }
  
  if (loopState == LOOP_STATE_STARTED) {
    sensorValue = analogRead(analogInPin);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Midiendo vibración ...");

    if (sensorValue != 0 && (sensorValue > 530 || sensorValue < 490)) { 
      if (!triggerActivated) {
        triggerActivated = true;
        Serial.println("Se ha disparado el medidor debido a que el valor del sensor es : " + (String) sensorValue );
      }
    }

    if (triggerActivated) {   
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sensor disparado ...");
      unsigned long currentMicros = micros();

      if (currentMicros - previousMicros >= interval) {
        previousMicros = currentMicros;
        saveData(currentMicros, sensorValue);
      }
      
      sensorValue = analogRead(analogInPin);
      
      outputValue = map(sensorValue, 0, 1023, 0, 255);

      Serial.print("sensor = ");
      Serial.print(sensorValue);
      Serial.print("\t output = ");
      Serial.println(outputValue);
    }
  }
}

```

