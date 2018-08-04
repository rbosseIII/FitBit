#include <Arduino.h>
#include <SparkFun_ADXL345.h>
#include <SPI.h>
#include <Wire.h>
#include <math.h>

//#defines go here
typedef struct
{
  float x, y, z;
} Accel;

class ADXL{
    public:
        static ADXL* getInstance();
        void setupADXL345();
        void readADXL(Accel*);
        void writeADXL(uint8_t, uint8_t);
        int formatX(uint8_t*);
        int formatY(uint8_t*);
        int formatZ(uint8_t*);
        ADXL345* adxllib;
        ADXL345* getLib();
        void setTapDetection();
        void setInterrupts();
        void clearInerrupts();
        void readFIFO(uint16_t * pArray, int size, Accel* accel);
        void setFifo();
    
    private:
        ADXL();
        static ADXL* _pInstance;

};