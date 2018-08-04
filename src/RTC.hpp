#include <Arduino.h>
#include <Wire.h>
#include <MCP7940.h>

#define CONTROLCODE 0x6F

const uint8_t ALARMALLMASK = 7;

class RTC{
    public:
        static RTC* getInstance();
        void setupRTC();
        MCP7940_Class* rtclib;
        MCP7940_Class* getLib();
        uint8_t bcdToDec(uint8_t val);
        bool setTimer(uint32_t sec, uint8_t alarm);
        DateTime* getTime();
        void printTime();

    private:
        RTC();
        static RTC* _pInstance;
        DateTime* now;
};