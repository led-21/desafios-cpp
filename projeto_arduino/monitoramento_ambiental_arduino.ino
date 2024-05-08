#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>

//Definitions
#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
//#define calibration_button 13 //Pin to calibrate your sensor

#define MQ135_DEFAULTPPM 399 //default ppm of CO2 for calibration
#define MQ135_DEFAULTRO 68550 //default Ro for MQ135_DEFAULTPPM ppm of CO2
#define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
#define MQ135_EXPONENT -2.769034857 //CO2 gas value
#define MQ135_MAXRSRO 2.428 //for CO2
#define MQ135_MINRSRO 0.358 //for CO2

/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

#define DHTPIN 2
#define DHTTYPE DHT21  

DHT_Unified dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4); 

uint32_t delayMS;

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  
  dht.begin();
  lcd.init();   // initialize the lcd 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  
  lcd.print("Ola Gabrielle!");
  Serial.begin(9600);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delay(3000);

  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setA(102.2); MQ135.setB(-2.473); // Configure the equation to to calculate NH4 concentration

  /*
    Exponential regression:
  GAS      | a      | b
  CO       | 605.18 | -3.937  
  Alcohol  | 77.255 | -3.18 
  CO2      | 110.47 | -2.862
  Toluen  | 44.947 | -3.445
  NH4      | 102.2  | -2.473
  Aceton  | 34.668 | -3.369
  */

  MQ135.init(); 
  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ135.setRL(10);
  */
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0/10);
  Serial.println("  done!.");
  /*****************************  MQ CAlibration ********************************************/ 
  MQ135.serialDebug(true);

  delayMS = 2000;
}

void loop() {
  //Read data and store it to variables hum and temp
  delay(delayMS);

  sensors_event_t event;
  String result ="";

  float cFactor = 0;
  if (!isnan(event.temperature) && !isnan(event.relative_humidity)) cFactor = getCorrectionFactor(event.temperature, event.relative_humidity);

  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ135.readSensor(false, cFactor); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
 // MQ135.serialDebug(); // Will print the table on the serial port

  //LCD Print
  lcd.clear();
  lcd.setCursor(0,0);

  dht.temperature().getEvent(&event);
  lcd.print("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(event.temperature,1);
  lcd.setCursor(10,0);

  result+= String(event.temperature) +",";

  dht.humidity().getEvent(&event);
  lcd.print("U: ");
  lcd.setCursor(12,0);
  lcd.print(event.relative_humidity,1);  

  result+= String(event.relative_humidity)+",";

  lcd.setCursor(0,1);
  lcd.print("Mq: ");
  lcd.setCursor(3,1);
  lcd.print(MQ135.readSensor(),1);  
  lcd.setCursor(3,1);
  lcd.setCursor(7,1);
  lcd.print("PPM");

  Serial.println(result+MQ135.readSensor());  
}

float getCorrectionFactor(float t, float h) {
  return CORA * t * t - CORB * t + CORC - (h-33.)*CORD;
}

float getCorrectedResistance(long resvalue, float t, float h) {
  return resvalue/getCorrectionFactor(t, h);
}

float getCorrectedPPM(long resvalue,float t, float h, long ro) {
  return PARA * pow((getCorrectedResistance(resvalue, t, h)/ro), -PARB);
}
