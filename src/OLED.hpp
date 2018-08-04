#include <SFE_MicroOLED.h>

class OLED{
    public:
        static OLED* getInstance();
        void setUpOLED();
        MicroOLED* oledlib;
        MicroOLED* getLib();
        void sleep();
        void wakeup();

    private:
        OLED();
        static OLED* _pInstance;
};