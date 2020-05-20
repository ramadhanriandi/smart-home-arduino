#include <Wire.h>

#define SLAVE_ADDR 9

int blueLED = 11;
int x = 0;

int yellowLED = 13;

int ultrasonicSensor = 7;

void setup()
{
  pinMode (blueLED, OUTPUT);
  pinMode (yellowLED, OUTPUT);
  
  Wire.begin(SLAVE_ADDR); 
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);
}

void receiveEvent(int bytes) {
  x = Wire.read();
}

void loop() {
  long duration, distance;
  pinMode(ultrasonicSensor, OUTPUT);
  digitalWrite(ultrasonicSensor, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicSensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultrasonicSensor, LOW);
  
  pinMode(ultrasonicSensor, INPUT);
  duration = pulseIn(ultrasonicSensor, HIGH);

  distance = microsecondsToCentimeters(duration);
  
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  
  if (distance > 100) {
  	digitalWrite(yellowLED, HIGH); 
  } else {
  	digitalWrite(yellowLED, LOW); 
  }
  
  int ledPWM = map(x, 0, 255, 0, 1023);
  analogWrite(blueLED,ledPWM);
  Serial.print("X is: ");
  Serial.println(x);
  Serial.print("PWM is: ");
  Serial.println(ledPWM);
  delay(1000);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}