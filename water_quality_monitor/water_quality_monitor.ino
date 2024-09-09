#define BLYNK_TEMPLATE_ID "TMPL64KqQxK1u"
#define BLYNK_TEMPLATE_NAME "Water Quality Monitoring System"

#include <WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <BlynkSimpleEsp32.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows


#define TdsSensorPin 25 // pin TDS
#define turbidPin 26    // pin turbidity
#define potPin 27       // pin pH
#define oneWireBus 4    // pin temperature
#define VREF 3.3        // analog reference voltage(Volt) of the ADC
#define SCOUNT 30       // sum of sample point

int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;   
float tdsValue = 0;
float temperature = 25; // current temperature for compensation

float ph;
float Value = 0;
unsigned long previousMillis = 0;
const long interval = 1000; // Interval at which to update display (milliseconds)
   
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// WiFi SSID and Password
char auth[] = "vrsVw1lk9ism2wSEppp9Ag2xToUPK9gt";
char SSID[] = "Redmi 10 2022";
char pass[] = "@Devin373";

// median filtering algorithm
int getMedianNum(int bArray[], int iFilterLen){
  int bTab[iFilterLen];
  for (byte i = 0; i<iFilterLen; i++)
  bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0){
    bTemp = bTab[(iFilterLen - 1) / 2];
  }
  else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}

BlynkTimer timer;

void setup(){
  lcd.init(); // initialize the lcd
  lcd.backlight(); // open the backlight 
  
  lcd.setCursor(0, 0);
  lcd.print("    Water Quality   ");
  lcd.setCursor(0, 1);
  lcd.print("  Monitoring System ");
  lcd.setCursor(0, 2);
  lcd.print("       TFI KSE      ");
  lcd.setCursor(0, 3);
  lcd.print("        2024        ");

  Serial.begin(115200);
  Blynk.begin(auth, SSID, pass);
  pinMode(TdsSensorPin, INPUT);
  pinMode(potPin, INPUT);
  sensors.begin();
  delay(2000);
  lcd.clear();
}

void loop(){ 
  Blynk.run();
  static unsigned long analogSampleTimepoint = millis();
  if(millis()-analogSampleTimepoint > 40U){                         // every 40 milliseconds, read the analog value from the ADC
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);     // read the analog value and store into the buffer
    analogBufferIndex++;
    if(analogBufferIndex == SCOUNT){ 
      analogBufferIndex = 0;
    }
  }   
  
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 800U){
    printTimepoint = millis();
    for(copyIndex=0; copyIndex<SCOUNT; copyIndex++){
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
      
      // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 4096.0;
      
      //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
      float compensationCoefficient = 1.0+0.02*(temperature-25.0);
      //temperature compensation
      float compensationVoltage=averageVoltage/compensationCoefficient;
      
      //convert voltage value to tds value
      tdsValue = (133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
    }
      Serial.print("voltage TDS:");
      Serial.print(averageVoltage);
      Serial.print("V   ");
      Serial.print("TDS Value:");
      Serial.print(tdsValue);
      Serial.println("ppm");
  }

  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.print("ºC | ");
  Serial.print(temperatureF);
  Serial.println("ºF");

  Value = analogRead(potPin);
  Serial.print(Value);
  Serial.print(" | ");
  float voltage_pH = Value * (3.3 / 4096.0);
  ph = (3.3 * voltage_pH);
  Serial.println(ph);

  int sensorValue = analogRead(turbidPin);
  float voltage_turbid = sensorValue * (3.3 / 4096.0);
  Serial.println("Turbidity Output (V):");
  Serial.print(voltage_turbid);
  float NTU = -909.09*voltage_turbid + 3000;
  Serial.print(" | ");
  Serial.println(NTU);
  Serial.println();

  Blynk.virtualWrite(V0, ph);
  Blynk.virtualWrite(V1, NTU);
  Blynk.virtualWrite(V2, temperatureC);
  Blynk.virtualWrite(V3, tdsValue);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
        lcd.setCursor(0, 3);
        lcd.print("Suhu : ");
        lcd.print(temperatureC,2);
        lcd.print(" C            ");
        lcd.setCursor(0, 2);
        lcd.print("TDS  : ");
        lcd.print(tdsValue,2);
        lcd.print(" ppm          ");
        lcd.setCursor(0, 1);
        lcd.print("NTU  : ");
        lcd.print(NTU,0);
        lcd.print(" NTU          ");
        lcd.setCursor(0, 0);
        lcd.print("pH   : ");
        lcd.print(ph,2);
  }
}
