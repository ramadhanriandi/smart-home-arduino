#include <LiquidCrystal.h>
#include <Wire.h>

#define SLAVE_ADDR 9

LiquidCrystal lcd(5,6,8,9,10,11);

int redLED = 2;
int greenLED = 3;

int buzzer = 4;

int smokeSensor = A0;
int smokeSensorThresh = 400;

int tempSensor = A1;
int tempSensorThresh = 50;

int pirSensor = 12;

int x = 0;
int potentioSensor = A2;

void setup()
{
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
 
  pinMode(smokeSensor, INPUT);
  pinMode(tempSensor, INPUT);
  pinMode(pirSensor, INPUT);
  
  Wire.begin();
  
  Serial.begin(9600);
  
  lcd.begin(16, 2);
}

void loop()
{
  int smokeAnalogValue = analogRead(smokeSensor);
  float tempAnalogValue = analogRead(tempSensor);
  float tempValueMv = tempAnalogValue*5000/1024;
  float tempValueC = (tempValueMv/10)+(-50);
  int pirDigitalValue = digitalRead(pirSensor);
  int potentioValue = analogRead(potentioSensor);
  
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(potentioValue);
  Wire.endTransmission();
  
  if ((smokeAnalogValue > smokeSensorThresh) && (tempValueC > tempSensorThresh)) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    
    tone(buzzer, 1000, 10000);
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("ALERT");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("FIRE!");
    delay(1000);
  } else {
  	digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    
    noTone(buzzer);
    
    if (pirDigitalValue == HIGH) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MOTION DETECTED");
      delay(1000); 
    } else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("SAFE");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(" CLEAR");
      delay(1000);
    }
  }
}