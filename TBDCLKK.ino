#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2); //SCL A5 SDA A4
#include "DHT.h"            
const int DHTPIN = 4;      
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
int measurePin = A0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
void setup() {
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  dht.begin();
  lcd.init();                    
  lcd.backlight();       
}
void loop() {
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 
  Serial.print("Nhiet do: ");
  Serial.println(t);               
  Serial.print("Do am: ");
  Serial.println(h);                 
  
   digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;
  Serial.println(dustDensity); // unit: ug/m3
  lcd.clear();
  lcd.print("DoAm:");
  lcd.setCursor(6,0);
  lcd.print(h);
  delay(3000);
  lcd.clear();
  lcd.print("NhietDo:");
  lcd.setCursor(9,0);
  lcd.print(t);
  delay(3000);
  lcd.clear();
  lcd.print("BuiPM2.5:");
  lcd.setCursor(9,0);
  lcd.print(dustDensity);
  delay(3000);
}
