#include <Arduino.h>
#include <math.h>

//#defines go here

class STEPCOUNT{
    public:
        static STEPCOUNT* getInstance();
        uint8_t calculateSteps(uint8_t* fifo);
        

    private:
        STEPCOUNT();
        static STEPCOUNT* _pInstance;
        uint8_t tempStorage[32];
};