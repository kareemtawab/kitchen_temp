#include <Arduino.h>
#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Timer.h> // the beautiful library by Simon Monk, Damian Philipp and Jack Christensen. Big thanks to them.

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 12

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

U8G2_PCD8544_84X48_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 6, /* data=*/ 5, /* cs=*/ 3, /* dc=*/ 4, /* reset=*/ 2);  // Nokia 5110 Display

Timer timer; // timer function for the Timer.h library

float t;
int BL = 11;

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  u8g2.begin();
  sensors.begin();
  sensors.setResolution(12);
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  timer.every(350, dallastempget);
  analogWrite(BL, 240);
}

void loop(void) {
  timer.update();
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  u8g2.setFont(u8g2_font_logisoso34_tn);
  u8g2.setCursor(3, 34);
  u8g2.print(t, 1);
  u8g2.setFont(u8g2_font_guildenstern_nbp_tr);
  u8g2.drawStr(0, 47, "Temperature( C)");
  u8g2.drawFrame(70,38,3,3); // for the degree symbol
  //u8g2.setFontDirection(3);
  //u8g2.setFont(u8g2_font_p01type_tn);
  //u8g2.drawStr(54, 25, "08/12");
  u8g2.sendBuffer();
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void dallastempget() {
  t = sensors.getTempCByIndex(0);
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();
  digitalWrite(LED_BUILTIN, HIGH);
}
