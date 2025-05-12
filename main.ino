#include "aip16c22.h"


float temperature_celcius = 34.5; // C
float temperature_fahrenheit = 89.5; // F
float humidity = 66.1; // %
uint8_t battery = 40; // 0-100 percentage

AIP16C22 display;

void setup() {
  display.displayInit();

}


void loop() {
  display.printBattLevel(battery);
  delay(1000);
  display.updateIcon(display.BLE_ICON, true); // turn on ble icon
  delay(500);
  display.updateIcon(display.FIRE_ICON, true); // turn on fire icon
  delay(500);
  display.updateIcon(display.SUN_ICON, true); // turn on sun icon
  delay(500);
  display.updateIcon(display.FROST_ICON, true); // turn on frost icon
  delay(500);
  display.updateIcon(display.HUMIDITY_ICON, true); // turn on huidity icon

  delay(1000);
  display.updateIcon(display.BLE_ICON, false); // turn off ble icon
  delay(500);
  display.updateIcon(display.FIRE_ICON, false); // turn off fire icon
  delay(500);
  display.updateIcon(display.SUN_ICON, false); // turn off sun icon
  delay(500);
  display.updateIcon(display.FROST_ICON, false); // turn off frost icon
  delay(500);
  display.updateIcon(display.HUMIDITY_ICON, false); // turn off humidity icon

  display.printHumidity(humidity);
  display.printTemperature(temperature_celcius);
  display.printTemperature(temperature_fahrenheit, true);

  display.printBattLevel(80); // show battery 80% = 4 bars
  delay(5000);
  display.displayClear();
}