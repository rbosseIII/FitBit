#include<Arduino.h>
#include<Wire.h>
#include <RTCC_MCP7940N.h>

/**
 * RTC_MCP7940N is authored by kanewallmann and can be found at:
 * https://github.com/kanewallmann/rtcc-MCP7940N-arduino/blob/master/RTCC_MCP7940N.cpp
 * I take no credit for this library.
 */

typedef struct
{
  uint16_t month, day, year;
  uint16_t hour, minute, second;
} DateTime;

class MCP{
    public:
        MCP();
        virtual ~MCP();
        void setupRTC(DateTime*);
        void readRTC(DateTime*);
        uint8_t bcdToDec(uint8_t);
};