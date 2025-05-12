#ifndef AIP16C22_H
#define AIP16C22_H

#include "Arduino.h"

#define AIP16C22_ADDR 0x3F


class AIP16C22 {
  public:
    AIP16C22() {}
    ~AIP16C22() {}

    enum Icon {
      BLE_ICON,       // S1 (SEG0, COM0)
      WIFI_ICON,      // S2 (SEG0, COM1)
      TEMP_LEADING_1, // S3 (SEG7, COM0)
      TEMP_UNIT_S4,   // S4 (SEG2, COM0)
      TEMP_UNIT_S5,   // S5 (SEG2, COM1)
      TEMP_UNIT_S6,   // S6 (SEG3, COM0)
      FROST_ICON,     // S7 (SEG2, COM3)
      FIRE_ICON,      // S8 (SEG2, COM3)
      SEPARATOR,      // S9 (SEG15, COM1)
      HUMIDITY_ICON,  // S10 (SEG15, COM2)
      SUN_ICON,       // S11 (SEG15, COM3)
      PERCENT_ICON,   // S12 (SEG9, COM0)
      BATT_BAR0,      // BT0 (SEG1, COM0)
      BATT_BAR1,      // BT1 (SEG1, COM1)
      BATT_BAR2,      // BT2 (SEG1, COM2)
      BATT_BAR3,      // BT3 (SEG1, COM3)
      BATT_BAR4,      // BT4 (SEG0, COM3)
      BATT_BAR5,      // BT5 (SEG0, COM2)
      TEMP_DP,        // P1 (SEG5, COM0)
      HUMIDITY_DP     // P2 (SEG11, COM0)
    };
    


    typedef struct {
        uint8_t address;
        uint8_t com;
    } IconMapping;


    // icons address and com mapping
    IconMapping iconMap[20] = {
      // Address  COM    // Function            (Hardware COM → Code COM)
      {0x00, 0x01}, // BLE_ICON,       // S1 (SEG0, COM0)
      {0x00, 0x02}, // WIFI_ICON,      // S2 (SEG0, COM1)
      {0x03, 0x10}, // TEMP_LEADING_1, // S3 (SEG7, COM0)
      {0x01, 0x01}, // TEMP_UNIT_S4,   // S4 (SEG2, COM0)
      {0x01, 0x02}, // TEMP_UNIT_S5,   // S5 (SEG2, COM1)
      {0x01, 0x10}, // TEMP_UNIT_S6,   // S6 (SEG3, COM0)
      {0x01, 0x04}, // FROST_ICON,     // S7 (SEG2, COM2)
      {0x01, 0x08}, // FIRE_ICON,      // S8 (SEG2, COM3)
      {0x07, 0x20}, // SEPARATOR,      // S9 (SEG15, COM1)
      {0x07, 0x40}, // HUMIDITY_ICON,  // S10 (SEG15, COM2)
      {0x07, 0x80}, // SUN_ICON,       // S11 (SEG15, COM3)
      {0x04, 0x01}, // PERCENT_ICON,   // S12 (SEG9, COM0)
      {0x00, 0x10}, // BATT_BAR0,      // BT0 (SEG1, COM0)
      {0x00, 0x20}, // BATT_BAR1,      // BT1 (SEG1, COM1)
      {0x00, 0x40}, // BATT_BAR2,      // BT2 (SEG1, COM2)
      {0x00, 0x80}, // BATT_BAR3,      // BT3 (SEG1, COM3)
      {0x00, 0x08}, // BATT_BAR4,      // BT4 (SEG0, COM3)
      {0x00, 0x04}, // BATT_BAR5,      // BT5 (SEG0, COM2)
      {0x02, 0x10}, // TEMP_DP,        // P1 (SEG5, COM0)
      {0x05, 0x10} // HUMIDITY_DP      // P2 (SEG11, COM0)
    };

    // Digit segment mapping structure
    typedef struct {
        IconMapping segmentA;
        IconMapping segmentB;
        IconMapping segmentC;
        IconMapping segmentD;
        IconMapping segmentE;
        IconMapping segmentF;
        IconMapping segmentG;
    } DigitSegments;

    // Temperature Segments address and com mapping // Temperature digits (1A-3G)
    DigitSegments tempDigits[3] = {
      // Digit 1 (1A-1G)
      { {0x04, 0x01},  // A (SEG8, COM0)
        {0x03, 0x20},  // B (SEG7, COM1)
        {0x03, 0x80},  // C (SEG7, COM3)
        {0x04, 0x08},  // D (SEG8, COM3)
        {0x04, 0x04},  // E (SEG8, COM2)
        {0x04, 0x02},  // F (SEG8, COM1)
        {0x03, 0x40} },// G (SEG7, COM2)
      
      // Digit 2 (2A-2G)
      { {0x03, 0x01},  // A (SEG6, COM0)
        {0x02, 0x20},  // B (SEG5, COM1)
        {0x02, 0x80},  // C (SEG5, COM3)
        {0x03, 0x08},  // D (SEG6, COM3)
        {0x03, 0x04},  // E (SEG6, COM2)
        {0x03, 0x02},  // F (SEG6, COM1)
        {0x02, 0x40} },// G (SEG5, COM2)
      
      // Digit 3 (3A-3G) - decimal part
      { {0x02, 0x01},  // A (SEG4, COM0)
        {0x01, 0x20},  // B (SEG3, COM1)
        {0x01, 0x80},  // C (SEG3, COM3)
        {0x02, 0x08},  // D (SEG4, COM3)
        {0x02, 0x04},  // E (SEG4, COM2)
        {0x02, 0x02},  // F (SEG4, COM1)
        {0x01, 0x40} } // G (SEG3, COM2)
    };


    // Humidity Segments address and com mapping // Humidity digits (4A-6C)
    DigitSegments humidityDigits[3] = {
      // Digit 4 (4A-4G)
      { {0x07, 0x01},  // A (SEG14, COM0)
        {0x06, 0x20},  // B (SEG13, COM1)
        {0x06, 0x80},  // C (SEG13, COM3)
        {0x07, 0x08},  // D (SEG14, COM3)
        {0x07, 0x04},  // E (SEG14, COM2)
        {0x07, 0x02},  // F (SEG14, COM1)
        {0x06, 0x40} },// G (SEG13, COM2)
      
      // Digit 5 (5A-5G)
      { {0x06, 0x01},  // A (SEG12, COM0)
        {0x05, 0x20},  // B (SEG11, COM1)
        {0x05, 0x80},  // C (SEG11, COM3)
        {0x06, 0x08},  // D (SEG12, COM3)
        {0x06, 0x04},  // E (SEG12, COM2)
        {0x06, 0x02},  // F (SEG12, COM1)
        {0x05, 0x40} },// G (SEG11, COM2)
      
      // Digit 6 (6A-6G) - decimal part
      { {0x05, 0x01},  // A (SEG10, COM0)
        {0x04, 0x20},  // B (SEG09, COM1)
        {0x04, 0x80},  // C (SEG09, COM3)
        {0x05, 0x08},  // D (SEG10, COM3)
        {0x05, 0x04},  // E (SEG10, COM2)
        {0x05, 0x02},  // F (SEG10, COM1)
        {0x04, 0x40} } // G (SEG09, COM2)
    };

    const uint8_t digitPattern[10] = {
      0b00111111, // 0
      0b00000110, // 1
      0b01011011, // 2
      0b01001111, // 3
      0b01100110, // 4
      0b01101101, // 5
      0b01111101, // 6
      0b00000111, // 7
      0b01111111, // 8
      0b01101111  // 9
    };




    void displayInit(uint8_t address=AIP16C22_ADDR);
    void updateIcon(uint8_t icon, bool state);
    void displayClear();
    void printTemperature(float temp, bool fahrenheit = false);
    void printHumidity(float humidity);
    void printBattLevel(uint8_t percent);

  private:
    void sendCommand(uint8_t cmd);
    void setAddress(uint8_t addr);
    void writeData(uint8_t data);
    void writeSegment(uint8_t addr, uint8_t data);
    void updateDataOnAddress(IconMapping mapping, bool state);
    void displayDigit(uint8_t number, const DigitSegments& segments);

    uint8_t _address;

};




#endif // AIP16C22_H