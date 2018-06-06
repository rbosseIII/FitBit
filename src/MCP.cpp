#include <MCP.h>


#define CONTROLCODE 0x6F
#define RTCSEC 0x00
#define RTCMIN 0x01
#define RTCHOUR 0x02
#define RTCWKDAY 0x03
#define RTCDATE 0x04
#define RTCMTH 0x05
#define RTCYEAR 0x06

RTCC_MCP7940N rtc;

MCP::MCP(){
    //do nothing
    // device id is 0x6F
    // enable oscillator (set st bit), set hour and AM/PM mode
    // google BCD for "15", "1" goes in tens and "5" goes in ones
    //get two capacitors that are 12pF
}

MCP::~MCP(){
    //do nothing
}

uint8_t MCP::bcdToDec(uint8_t val)
{
  return ( (val/16*10) + (val%16) );
}

void MCP::setupRTC(DateTime* datetime){


    Wire.beginTransmission(CONTROLCODE);
    Wire.write(uint8_t(RTCSEC));
    //RTCSEC -> set seconds:54 seconds
    Wire.write(uint8_t(0x36));
    //RTCMIN -> set minutes: 26 minutes
    Wire.write(uint8_t(0x26));
    //RTCHOUR -> set hour: 6 hours and set to pm and 12 hour cycle
    Wire.write(uint8_t(0x66));
    //RTCWKDAY -> set day: Tuesday 
    Wire.write(uint8_t(0x02));
    //RTCDATE -> set date: 5
    Wire.write(uint8_t(0x05));
    //RTCMTH  -> set month: 6
    Wire.write(uint8_t(0x06));
    //RTCYEAR -> set year: 18
    Wire.write(uint8_t(0x18));
    //finish transmission then enable oscillator after
    Wire.endTransmission();

    delay(5);
    

    rtc.SetOscillatorEnabled(true);
	rtc.SetExternalOscillatorEnabled(0);

}

void MCP::readRTC(DateTime* datetime){
    
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