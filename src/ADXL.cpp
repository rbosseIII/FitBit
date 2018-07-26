#include <ADXL.hpp>

#define PWR_CTL 0x2Du
#define DATA_FORMAT 0x31u
#define DATA_SAMPLE 0x2cu
#define ADXLADDRESS 0x53


ADXL* ADXL::_pInstance = NULL;

ADXL* ADXL::getInstance(){
    if(!_pInstance)
    {
        _pInstance = new ADXL();
    }
    return _pInstance;
}

ADXL::ADXL(){
    //does nothing
}

void ADXL::setupADXL345(){
    adxllib = new ADXL345;
    adxllib->powerOn();
}
ADXL345* ADXL::getLib(){
    return adxllib;
}

void ADXL::readADXL(Accel* accel){
    uint8_t value[6];

    Wire.beginTransmission(ADXLADDRESS);
    Wire.write(0x32);
    Wire.endTransmission();
    delay(5);

    Wire.beginTransmission(ADXLADDRESS);
    Wire.requestFrom(ADXLADDRESS, 6);

    int i = 0;
    while(Wire.available()){
    value[i] = Wire.read();
    i++;
    }

    Wire.endTransmission();
    delay(5);

    int x = formatX(value);
    int y = formatY(value);
    int z = formatZ(value);

    accel -> x = x;
    accel -> y = y;
    accel -> z = z;
}


int ADXL::formatX(uint8_t* array){
    int x = ((int)array[0]|((int)array[1]<<8));
    return x;
}

int ADXL::formatY(uint8_t* array){
    int y = ((int)array[2]|((int)array[3]<<8));
    return y;
}

int ADXL::formatZ(uint8_t* array){
    int z = ((int)array[4]|((int)array[5]<<8));
    return z;
}
