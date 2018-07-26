#include <OLED.hpp>

#define DC_JUMPER 0
#define PIN_RESET A5

OLED* OLED::_pInstance = NULL;

OLED::OLED(){
    
}

void OLED::setUpOLED(){
    oledlib = new MicroOLED(PIN_RESET,DC_JUMPER);
    oledlib->begin();
    oledlib->clear(ALL);
    oledlib->display();
    oledlib->setFontType(1);
    oledlib->clear(PAGE);
    oledlib->setCursor(0,0);
}

OLED* OLED::getInstance(){
    if(!_pInstance)
    {
        _pInstance = new OLED();
    }
    return _pInstance;
}

MicroOLED* OLED::getLib(){
    return oledlib;
}

