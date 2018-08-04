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

void ADXL::readFIFO(uint16_t * pArray, int size, Accel* accel){
    for(int i= 0; i<size; i++){
        readADXL(accel);
        int mag = sqrt(sq(accel->x)+sq(accel->y)+sq(accel->z));
        *(pArray+i) = mag;
    }
}

void ADXL::setupADXL345(){
    adxllib = new ADXL345;
    adxllib->powerOn();
    adxllib->setRangeSetting(4);
    adxllib->setRate(12.5); //12.5Hz
    clearInerrupts();
    adxllib->setActivityXYZ(1,1,1);
    adxllib->setActivityThreshold(75);
    adxllib->setInactivityXYZ(1,1,1);
    adxllib->setInactivityThreshold(75);
    adxllib->setTimeInactivity(10);
    setTapDetection();
    adxllib->setFreeFallThreshold(7);       // (5 - 9) recommended - 62.5mg per increment
    adxllib->setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment
    setFifo();
    adxllib->setImportantInterruptMapping(1,2,1,1,1,2);
    setInterrupts();
    adxllib->measure();
    
}

void ADXL::setFifo(){
    Wire.beginTransmission(ADXLADDRESS);
    Wire.write(0x38);
    Wire.write(0x7E);
    Wire.endTransmission();
}

void ADXL::clearInerrupts(){
    Wire.beginTransmission(ADXLADDRESS);
    Wire.write(0x2E);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(5);
}

void ADXL::setInterrupts(){
    adxllib->InactivityINT(0);
    adxllib->ActivityINT(0);
    adxllib->FreeFallINT(0);
    adxllib->doubleTapINT(1);
    adxllib->singleTapINT(0);
    adxllib->waterMarkINT(1);
}

void ADXL::setTapDetection(){
  adxllib->setTapDetectionOnXYZ(0,0,1);
  adxllib->setTapThreshold(50);           // 62.5 mg per increment
  adxllib->setTapDuration(15);            // 625 μs per increment
  adxllib->setDoubleTapLatency(80);       // 1.25 ms per increment
  adxllib->setDoubleTapWindow(200);       // 1.25 ms per increment
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
