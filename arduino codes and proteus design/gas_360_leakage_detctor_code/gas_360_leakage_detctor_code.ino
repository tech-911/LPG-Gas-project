#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int gasPin = A0;
int buzzer = 7;


void setup() {
  Serial.begin(9600);
  pinMode(gasPin,INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(32, 2);
  lcd.print("Gas Detector");
  lcd.setCursor(0, 1);
  lcd.print("Gas 360");
  delay(3000);
}

void loop() { 
  int gasSensor = analogRead(gasPin);
if(gasSensor >= 210){
  Serial.println(gasSensor);
  //digitalWrite(buzzer, HIGH);
  tone(buzzer, 1000, 500);
  lcd.clear();
  lcd.print("LPG Gas Leakage");
  lcd.setCursor(0, 1);
  Serial.println("  LPG Gas Leakage Detected!!!  ");
  lcd.print("  Detected!!!  ");
  delay(400);
  digitalWrite(buzzer, LOW);
  delay(500);
}

else{
  Serial.println(gasSensor);
  //digitalWrite(buzzer, LOW);
  //tone(buzzer, 2500, 800);
  lcd.clear();
  lcd.print("  No LPG Gas ");
  lcd.setCursor(0, 1);
  Serial.println("   No LPG Gas Leakage    ");
  lcd.print("    Leakage    ");
  delay(1000);
}
}
