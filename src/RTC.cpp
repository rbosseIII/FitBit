#include <RTC.hpp>

RTC::RTC(){
    //do nothing
}

RTC* RTC::_pInstance = NULL;

RTC* RTC::getInstance(){
    if(!_pInstance)
    {
        _pInstance = new RTC();
    }
    return _pInstance;
}


void RTC::setupRTC(){
   rtclib = new MCP7940_Class();
   now = new DateTime();
   rtclib->begin();
   rtclib->deviceStatus();
   rtclib->deviceStart();
   rtclib->adjust();

   now = getTime();
}

bool RTC::setTimer(uint32_t timeToPop, uint8_t alarm){
    return rtclib->setAlarm(alarm,ALARMALLMASK,DateTime(getTime()->unixtime() + timeToPop), 1);
}


MCP7940_Class* RTC::getLib(){
    return  rtclib;
}

uint8_t RTC::bcdToDec(uint8_t val){
    return ( (val/16*10) + (val%16) );
}

DateTime* RTC::getTime(){
    *now = rtclib->now();

    return now;
}

void RTC::printTime(){
    getTime();
    Serial.println(now->unixtime());
}
