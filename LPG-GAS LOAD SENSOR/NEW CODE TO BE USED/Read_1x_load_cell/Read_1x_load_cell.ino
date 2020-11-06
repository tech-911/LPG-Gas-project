#include <HX711_ADC.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 9, d5 = 10, d6 = 8, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
long t;
float p_wgt, n_wgt = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting...");
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();

  LoadCell.begin();
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = -1419.13; // uncomment this if you want to set the calibration value in the sketch

  //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom
  long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  
  LoadCell.setCalFactor(calibrationValue);
}

void loop() {
  static boolean newDataReady = 0;
  if (LoadCell.update()) newDataReady = true;
  
  float i = LoadCell.getData();
  n_wgt = i;
  if (abs(n_wgt - p_wgt) >= 1){
    Serial.println("Calculating... ");
    lcd.print("Calculating... ");
    delay(1000);
    lcd.clear();
    p_wgt = n_wgt;
  }
  else{
    lcd.clear();
    Serial.print("Load_cell output val: ");
    Serial.println(i);
    lcd.print("Wgt: ");
    lcd.print(i);
    lcd.print("g");
    delay(1000);
    lcd.clear();
    p_wgt = n_wgt;
  }
}
