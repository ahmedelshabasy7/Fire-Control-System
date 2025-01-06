#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int tempSensorPin = A0; 
const int redLedPin = 8;      
const int buzzerPin = 9;     
const int warningThreshold = 60;
const int dangerThreshold = 100; 

void setup() {
  
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Temp Sensor");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {
 
  int sensorValue = analogRead(tempSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  int temperature = (voltage - 0.5) * 100;      

  lcd.setCursor(0, 0); 
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C   ");
  

  if (temperature > dangerThreshold) {  
    lcd.setCursor(0, 1);
    lcd.print(" Run away NOW! ");
    tone(buzzerPin, 2000); 
    digitalWrite(redLedPin, HIGH);   
  }
  else if (temperature > warningThreshold) {
    lcd.setCursor(0, 1);  
    lcd.print(" Warning: FIRE! ");
    tone(buzzerPin, 1200);   
    digitalWrite(redLedPin, LOW);   
  } 
  else {
    lcd.setCursor(0, 1); 
    lcd.print("      Safe      "); 
    digitalWrite(redLedPin, LOW); 
    noTone(buzzerPin); 
  }

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Temp: ");
  Serial.println(temperature);

  delay(500);
}
