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


void RTC::setupRTC(rtcc_time* rtccTime){
    rtclib = new RTCC_MCP7940N;

    setRTCTime(rtccTime);

    rtclib->SetOscillatorEnabled(1);
    rtclib->SetExternalOscillatorEnabled(0);
}

RTCC_MCP7940N* RTC::getLib(){
    return  rtclib;
}

void RTC::readRTC(DateTime* datetime){
    // Set read address to 0
    Wire.beginTransmission(CONTROLCODE);
    Wire.write(0);
    Wire.endTransmission();

    // Request 7 byte Time and Date registers
    Wire.requestFrom(CONTROLCODE, 7, true);

    byte time_data[7];
    Wire.readBytes(time_data, 7);

    datetime->hour = bcdToDec(time_data[2] & 0x1F);
    datetime->minute = bcdToDec(time_data[1]);
    datetime->second = bcdToDec(time_data[0] & 0x7F);
    datetime->day = bcdToDec(time_data[4]);
    datetime->month = bcdToDec(time_data[5] & 0x1F);
    datetime->year = bcdToDec(time_data[6]);
}

void RTC::setRTCTime(rtcc_time* rtccTime){
    Wire.beginTransmission(CONTROLCODE);
    Wire.write(uint8_t(0x00));
    //RTCSEC -> set seconds:54 seconds
    Wire.write(uint8_t(0x36));
    //RTCMIN -> set minutes: 26 minutes
    Wire.write(uint8_t(0x21));
    //RTCHOUR -> set hour: 6 hours and set to pm and 12 hour cycle
    Wire.write(uint8_t(0x68));
    //RTCWKDAY -> set day: Tuesday 
    Wire.write(uint8_t(0x03));
    //RTCDATE -> set date: 5
    Wire.write(uint8_t(0x25));
    //RTCMTH  -> set month: 6
    Wire.write(uint8_t(0x07));
    //RTCYEAR -> set year: 18
    Wire.write(uint8_t(0x18));
    //finish transmission then enable oscillator after
    Wire.endTransmission();

    delay(5);

}

uint8_t RTC::bcdToDec(uint8_t val){
    return ( (val/16*10) + (val%16) );
}
