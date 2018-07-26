#include <Arduino.h>
#include <Wire.h>

class EEPROM{
    public:
        static EEPROM* getInstance();
        void setupEEPROM();
        void writeDataToEEPROM(uint16_t*,uint16_t);
        void readDataFromEEPROM(uint16_t*,uint16_t);

    private:
        EEPROM();
        static EEPROM* _pInstance; 
};