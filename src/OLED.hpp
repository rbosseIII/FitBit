#include <SFE_MicroOLED.h>

class OLED{
    public:
        static OLED* getInstance();
        void setUpOLED();
        MicroOLED* oledlib;
        MicroOLED* getLib();

    private:
        OLED();
        static OLED* _pInstance;
};