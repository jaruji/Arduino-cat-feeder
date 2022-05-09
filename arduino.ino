#include <Servo.h>
#include <RTClib.h>
#include "pitches.h"

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
#define SPEAKER_PIN 12
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;
unsigned long t = 0;
boolean hasRun;

//ThreeWire myWire(4,5,2); // IO, SCLK, CE
//virtuabotixRTC RTC(5,4,2);
DS1302 rtc(2, 7, 6);
char buf[20];


const int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

Servo servo;

void setup() {
  Serial.begin(9600);
//  Serial.begin(57600); delay(10);
  rtc.begin();
//  LoadCell.begin();
//  float calibrationValue;
//  EEPROM.get(calVal_eepromAdress, calibrationValue);
//  unsigned long stabilizingtime = 2000;
//  boolean _tare = true;
//  LoadCell.start(stabilizingtime, _tare);
//  if (LoadCell.getTareTimeoutFlag()) {
//    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
//    while (1);
//  }
//  else {
//    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
//    Serial.println("Startup is complete");
//  }
  
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  servo.attach(8);
  servo.write(0);
  hasRun = false;
}

void loop() {
  DateTime now = rtc.now();
  byte hour = now.hour();
  byte minute = now.minute();
  byte second = now.second();
 
  if(minute % 1 == 0 && second == 0 && !hasRun){
    hasRun = true;
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(SPEAKER_PIN, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(SPEAKER_PIN);
    }
    servo.write(180);
    delay(1500);
    servo.write(0);
    delay(1500);
    hasRun = false;
  }
  else{
    Serial.println(now.tostr(buf));
    static boolean newDataReady = 0;
    const int serialPrintInterval = 0; //increase value to slow down serial print activity
      // check for new data/start next conversion:
//    if (LoadCell.update()) newDataReady = true;
    // get smoothed value from the dataset:
//    if (newDataReady) {
//      if (millis() > t + serialPrintInterval) {
//        float i = LoadCell.getData();
//        Serial.print("Load_cell output val: ");
//        Serial.println(i);
//        newDataReady = 0;
//        t = millis();
//      }
//    }
  
    // receive command from serial terminal, send 't' to initiate tare operation:
//    if (Serial.available() > 0) {
//      char inByte = Serial.read();
//      if (inByte == 't') LoadCell.tareNoDelay();
//    }
//  
//    // check if last tare operation is complete:
//    if (LoadCell.getTareStatus() == true) {
//      Serial.println("Tare complete");
//    }
//    delay(100);
  }
}
