#include <Arduino.h>
#include <Wire.h>
#include <RTCC_MCP7940N.h>

#define CONTROLCODE 0x6F

typedef struct
{
  uint16_t month, day, year;
  uint16_t hour, minute, second;
} DateTime;

class RTC{
    public:
        static RTC* getInstance();
        void setupRTC(rtcc_time* rtccTime);
        RTCC_MCP7940N* rtclib;
        RTCC_MCP7940N* getLib();
        uint8_t bcdToDec(uint8_t val);
        void readRTC(DateTime* dateTime);

    private:
        RTC();
        static RTC* _pInstance;
        void setRTCTime(rtcc_time* rtccTime);

};