#include <Arduino.h>
#include <Wire.h>

class EEPROM{
    public:
        EEPROM();
        virtual ~EEPROM();
        void setupEEPROM();
        void writeDataToEEPROM(uint16_t*,uint16_t);
        void readDataFromEEPROM(uint16_t*,uint16_t);
};