#include <Arduino.h>
#include <math.h>

//#defines go here
#define FIFOLENGTH 32
#define THRESHOLD 4950
#define OVERTHRESHOLD 12000


class STEPCOUNT{
    public:
        static STEPCOUNT* getInstance();
        void calculateSteps(int16_t* fifo, uint16_t* steps);
        void init();
        

    private:
        STEPCOUNT();
        static STEPCOUNT* _pInstance;
        int16_t* tempStorage = new int16_t[32];
        int16_t* tempStorage2 = new int16_t[32];
        int16_t* diffSum = new int16_t[32];
        void updateSteps(uint16_t* pdatas, uint8_t data);
        uint8_t findPeaks(int16_t* parray);
};