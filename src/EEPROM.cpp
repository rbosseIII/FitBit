#include <EEPROM.hpp>

#define CONTROLCODE 0x50

EEPROM* EEPROM::_pInstance = NULL;

EEPROM::EEPROM(){
    //address id is 0x50 not 0xA0
    //write form is address id -> address high bit -> address low byte -> data
    //no need for start and stop bits
}


void EEPROM::setupEEPROM(){
    //don't need set up
}

EEPROM* EEPROM::getInstance(){
    if(!_pInstance)
    {
        _pInstance = new EEPROM();
    }
    return _pInstance;
}

void EEPROM::writeDataToEEPROM(uint16_t* data, uint16_t size){
    Wire.beginTransmission(CONTROLCODE);
    Wire.write(uint8_t (0 >> 8));
    Wire.write(uint8_t (0 & 0xFF));
    for(int i = 0; i < size; i++)
    {
        uint8_t upper = data[i] >> 8;
        uint8_t lower = data[i] & 0xFF;
        Wire.write(upper);
        Wire.write(lower);
    }
    Wire.endTransmission();
    delay(5);
}

void EEPROM::readDataFromEEPROM(uint16_t* buffer, uint16_t size){
    Wire.beginTransmission(CONTROLCODE);
    Wire.write(uint8_t (0 >> 8));
    Wire.write(uint8_t (0 & 0xFF));
    Wire.endTransmission();
    delay(5);
    Wire.requestFrom(0x50,size*2);
    if(Wire.available()){
        for(int i = 0; i < size; i++){
            uint16_t upper = Wire.read();
            uint16_t lower = Wire.read();
            buffer[i] = ((upper << 8) | lower);
        }
    }
}