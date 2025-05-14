#include "aip16c22.h"
#include "Wire.h"


AIP16C22 display;

void setup() {
  Serial.begin(115200);
  display.displayInit();

  display.updateIcon(display.BLE_ICON, true);
  display.updateIcon(display.FROST_ICON, true);
  display.updateIcon(display.FIRE_ICON, true);
  display.updateIcon(display.HUMIDITY_ICON, true);
  display.updateIcon(display.SUN_ICON, true);

  delay(2000);

  for(uint8_t i=0; i<=100; i+=20) {
    display.printBattLevel(i);
    delay(500);
  }

  display.printTemperature(30.4); // show celcius temperature
  delay(1000);
  display.printTemperature(55.8, true); // show fahrenheit temperature

  display.printHumidity(98.3);

  display.updateIcon(display.BLE_ICON, false);
  delay(1000);
  display.updateIcon(display.FROST_ICON, false);
  delay(1000);
  display.updateIcon(display.FIRE_ICON, false);
  delay(1000);
  display.updateIcon(display.HUMIDITY_ICON, false);
  delay(1000);
  display.updateIcon(display.SUN_ICON, false);
  delay(3000);
  display.displayClear();
}


void loop() { }

