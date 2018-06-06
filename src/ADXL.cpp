#include <ADXL.h>

#define PWR_CTL 0x2Du
#define DATA_FORMAT 0x31u

int CS = 5;

ADXL::ADXL(){
    //does nothing
}

ADXL::~ADXL(){
    //does nothing
}

void ADXL::setupADXL345(){
    //setup accel
    SPI.begin();
    SPI.setDataMode(SPI_MODE3);
    pinMode(CS,OUTPUT);
    digitalWrite(CS,HIGH);
    writeADXL(PWR_CTL, 0x0A);
    writeADXL(DATA_FORMAT, 0x00);
}

void ADXL::readADXL(Accel* accel){
    uint8_t value[6];
    //multi-bit read
    uint8_t address = 0xC0 | 0x32;
    //set chip select low, slave listen
    digitalWrite(CS, LOW);
    //read from address
    SPI.transfer(address);
    //dummy data
    for(int i = 0; i < 6; i++){
    value[i] = SPI.transfer(0x00);
    }
    //set chip select high, slave ignore
    digitalWrite(CS, HIGH);

    float x = formatX(value);
    float y = formatY(value);
    float z = formatZ(value);

    accel -> x = (x*.0039*9.81);
    accel -> y = (y*.0039*9.81);
    accel -> z = (z*.0039*9.81);
}

void ADXL::writeADXL(uint8_t address, uint8_t value){
    //set chip select low, slave listen
    digitalWrite(CS,LOW);
    //send accelerometer address
    SPI.transfer(address);
    //send value to that address
    SPI.transfer(value);
    //set chip select high, slave ignore
    digitalWrite(CS, HIGH);
}

float ADXL::formatX(uint8_t* array){
    float x = ((int)array[0]|((int)array[1]<<8));
    return x;
}

float ADXL::formatY(uint8_t* array){
    float y = ((int)array[2]|((int)array[3]<<8));
    return y;
}

float ADXL::formatZ(uint8_t* array){
    float z = ((int)array[4]|((int)array[5]<<8));
    return z;
}
