#include <Arduino.h>

#include <SPI.h>

//#defines go here
typedef struct
{
  float x, y, z;
} Accel;

class ADXL{
    public:
        ADXL();
        virtual ~ADXL();
        void setupADXL345();
        void readADXL(Accel*);
        void writeADXL(uint8_t, uint8_t);
        float formatX(uint8_t*);
        float formatY(uint8_t*);
        float formatZ(uint8_t*);
};