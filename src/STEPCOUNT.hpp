#include <Arduino.h>
#include <math.h>

//#defines go here
#define FIFOLENGTH 64


class STEPCOUNT{
    public:
        static STEPCOUNT* getInstance();
        void calculateSteps(uint8_t* fifo, uint8_t* steps);
        

    private:
        STEPCOUNT();
        static STEPCOUNT* _pInstance;
        uint8_t tempStorage[64];
        void updateSteps(uint8_t* pdatas);
};