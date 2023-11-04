/* SD section ---------------
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
 */
 #include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
// Button section ---------------
#include <ezButton.h>
#define LOOP_STATE_STOPPED 0
#define LOOP_STATE_STARTED 1
ezButton button(A3);  // create ezButton object that attach to pin A3 botó blanc;
int loopState = LOOP_STATE_STOPPED;

// Sensor section ---------------
const int analogInPin = A1;  // Analog input pin that the geophone is attached to


int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)
int llistaDeValors[100]; //freq 1k - 1s /1000    10m/s entre mostres hi ha 0.1s 

// LCD section ----------
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

//TODO ----------------------------------------------------- 
//1 llindar de valors quan supera 520 o 505 comença a guardar dades al array,
bool triggerActivated = false;
// cada 1 milisegon , guarda el valor de sensorValue al array pasar de millis() a micros() ✅
// quan l'array està ple

// Interruptions section ---------------
unsigned long previousMicros = 0;  // Almacena el tiempo anterior
const unsigned long interval = 500000; // Intervalo de tiempo en milisegundos (1 segundo = 1,000,000 micros) UTILITZAR FUNCIÓ MICROS //freq 1k - 1s /1000    10m/s entre mostres hi ha 0.1s

void saveData(unsigned long currentMicros, int sensorValue) {
  //ejecutar código para guardar archivo o variables en la SD memória
//  Serial.println("\n se ha ejecutado savedata");
//  Serial.println(currentMillis);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Value : " + (String) sensorValue);

  // guardar valors al array, al final de la presa de mostres s'envia a SD
}

void setup() {

  Serial.begin(9600);  // initialize serial communications at 9600 bps:
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing...");

}

void loop() {
  button.loop(); // call the loop() function first
  
  //boton On/Off programa
  if (button.isPressed()) {
    if (loopState == LOOP_STATE_STOPPED)
      loopState = LOOP_STATE_STARTED;
    else 
      loopState = LOOP_STATE_STOPPED; // podria añadir que se reinicie el trigger
  }
  // 🧧 quan esà ple array -> arxiu sd------------------------------------------------------ 
  if (loopState == LOOP_STATE_STARTED) {
    sensorValue = analogRead(analogInPin);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Midiendo vibración ...");

    if (sensorValue != 0 && (sensorValue > 530 || sensorValue < 490)) { 
      if (!triggerActivated) {
        //activo el trigger 🔻 
        triggerActivated = true;
        Serial.println("Se ha disparado el medidor debido a que el valor del sensor es : " + (String) sensorValue );
        //espero X segundos y apago el trigger ?🕗
      }
    }

    // en vez de un if un while? 🧀
    if (triggerActivated) {   
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sensor disparado ...");
      unsigned long currentMicros = micros();  // Obtiene el tiempo actual

      if (currentMicros - previousMicros >= interval) {
        // Si ha pasado el intervalo de tiempo deseado
        previousMicros = currentMicros;  // Guarda el tiempo actual como el tiempo anterior
        saveData(currentMicros, sensorValue);
      }
      

      //Código principal sensor----------
      sensorValue = analogRead(analogInPin); // read the analog in value: EL IMPORTANT ES AQUEST
      
      outputValue = map(sensorValue, 0, 1023, 0, 255); // map it to the range of the analog out: NO SIRVE PARA NADA , PERO AYUDA A LA GRAFICA 
      

      // print the results to the Serial Monitor:
      Serial.print("sensor = ");
      Serial.print(sensorValue);
      Serial.print("\t output = ");
      Serial.println(outputValue);

      // wait 2 milliseconds before the next loop for the analog-to-digital
      // converter to settle after the last reading:
      delay(2);
    }
  }

}
