#include "aip16c22.h"
#include "Wire.h"


void AIP16C22::sendCommand(uint8_t cmd) {
  Wire.beginTransmission(AIP16C22_ADDR);
  Wire.write(cmd);
  Wire.endTransmission();
}


void AIP16C22::writeSegment(uint8_t addr, uint8_t data) {
  Wire.beginTransmission(AIP16C22_ADDR);
  delay(10);
  Wire.write(addr);
  delay(10);
  Wire.write(data);
  delay(10);
  Wire.endTransmission();
}


void AIP16C22::displayInit(uint8_t address) {
  _address = address;
  Wire.begin();
  delay(100);
  // Configure display: 1/4 duty, 1/3 bias, display on, 80Hz
  sendCommand(0x8C);
  sendCommand(0xC0);
  displayClear();
}



// Clear all segments (addresses 0x00-0x15)
void AIP16C22::displayClear() {
  for(uint8_t addr = 0x00; addr <= 0x15; addr++) {
    writeSegment(addr, 0x00);
  }
}

/*
  This function is used to turn on/off segment based on state
*/
void AIP16C22::updateDataOnAddress(IconMapping mapping, bool state) {
  uint8_t currentData;
  
  // set Address to currect segment
  Wire.beginTransmission(AIP16C22_ADDR);
  Wire.write(mapping.address);
  Wire.endTransmission();
  
  Wire.requestFrom(AIP16C22_ADDR, 1); // get currect data of address
  if(Wire.available()) {
    currentData = Wire.read();
  }

  if(state) {
    currentData |= mapping.com;
  } else {
    currentData &= ~mapping.com;
  }
  
  writeSegment(mapping.address, currentData); // send updated data to address
}


/*
  This function is used to turn on/off ICONs
*/
void AIP16C22::updateIcon(uint8_t icon, bool state) {
  IconMapping mapping = iconMap[icon];
  updateDataOnAddress(mapping, state);
}



void AIP16C22::printTemperature(float temp, bool fahrenheit) {
  /*
    Set temperature unit icons
    either C for celcius or F to Fahrenheit
  */
  updateIcon(TEMP_UNIT_S4, true);
  updateIcon(TEMP_UNIT_S5, fahrenheit);
  updateIcon(TEMP_UNIT_S6, !fahrenheit);

  // Clear previous temperature digits
  // for(int i = 0; i < 3; i++) {
  //   displayDigit(10, tempDigits[i]);
  // }

  // Show leading 1 (S3) if temp > 99.9
  bool showLeading1 = (temp >= 100.0);
  updateIcon(TEMP_LEADING_1, showLeading1);
  if(showLeading1) temp -= 100.0;

  // Split into digits
  uint8_t digit1 = (int)(temp / 10.0) % 10;
  uint8_t digit2 = (int)temp % 10;
  uint8_t digit3 = (int)(temp * 10) % 10;

  // Display digits
  displayDigit(digit1, tempDigits[0]);
  displayDigit(digit2, tempDigits[1]);
  displayDigit(digit3, tempDigits[2]);

  updateIcon(TEMP_DP, true);
}


void AIP16C22::printHumidity(float humidity) {

  // Split into digits
  uint8_t digit1 = (int)(humidity / 10.0) % 10;
  uint8_t digit2 = (int)humidity % 10;
  uint8_t digit3 = (int)(humidity * 10) % 10;

  // Display digits
  displayDigit(digit1, humidityDigits[0]);
  displayDigit(digit2, humidityDigits[1]);
  displayDigit(digit3, humidityDigits[2]);

  // Show percentage icon and decimal point
  updateIcon(PERCENT_ICON, true);
  updateIcon(HUMIDITY_DP, true);
}


void AIP16C22::printBattLevel(uint8_t percent) {
  // Clear all battery bars
  // for(uint8_t i = BATT_BAR0; i <= BATT_BAR5; i++) {
  //   updateIcon(i, false);
  // }

  updateIcon(BATT_BAR0, true);
  uint8_t bars = min(percent / 20, 5);
  for(uint8_t i = 0; i < bars; i++) {
    updateIcon(BATT_BAR5 - i, true);
  }
}


void AIP16C22::displayDigit(uint8_t number, const DigitSegments& segments) {
  uint8_t pattern = digitPattern[number];
  
  updateDataOnAddress(segments.segmentA, pattern & 0x01); // A
  updateDataOnAddress(segments.segmentB, pattern & 0x02); // B
  updateDataOnAddress(segments.segmentC, pattern & 0x04); // C
  updateDataOnAddress(segments.segmentD, pattern & 0x08); // D
  updateDataOnAddress(segments.segmentE, pattern & 0x10); // E
  updateDataOnAddress(segments.segmentF, pattern & 0x20); // F
  updateDataOnAddress(segments.segmentG, pattern & 0x40); // G
}