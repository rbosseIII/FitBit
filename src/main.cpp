#include <Arduino.h>
#include <ADXL.hpp>
#include <EEPROM.hpp>
#include <Wire.h>
#include <OLED.hpp>
#include <RTC.hpp>
#include <math.h>

static boolean justBooted = true;
static boolean brownOut = false;

  uint8_t EF_Global;
//------------------------
const uint8_t EF_ADXL = 0x01;
const uint8_t EF_EEPROM = 0x02;
const uint8_t EF_RTC = 0x03;
const uint8_t EF_OLED = 0x04;
const uint8_t EF_I2C = 0x05;

  //uint8_t* TF_Global(5);
//------------------------
//First TF index
const uint8_t TF_ADXL_WATERMARK = 0x01;
const uint8_t TF_ADXL_DOUBLETAP = 0x02;
const uint8_t TF_ADXL_INACTIVITY = 0x03;
//Second TF index
const uint8_t TF_RTC_15MIN = 0x01;

void setupI2C(){
  Wire.begin(); //join i2c bus
  Wire.setClock(100000);
}


void setup() {
     /*
   * Configure all buses
   */
  setupI2C();
  /**
  * Initialize the EEPROM
  */
  EEPROM::getInstance()->setupEEPROM();
  /**
   * Configure the ADXL345
   */
  ADXL::getInstance()->setupADXL345();
  /**
   * Configure the OLED
   */
  OLED::getInstance()->setUpOLED();

  /**
   * Initialize configuration data for the RTC. Modify
   * the contents of the initConfig object such that the
   * RTC will begin with the correct values
   */
  rtcc_time initConfig;
  //rtclock.setupRTC(&initConfig);
  RTC::getInstance()->setupRTC(&initConfig);

  Serial.begin(9600);
}

Accel currentReading;
DateTime currentDateTime;
uint8_t totalSteps = 0;

void printScreen(){
  ADXL::getInstance()->readADXL(&currentReading);
  RTC::getInstance()->readRTC(&currentDateTime);
  OLED::getInstance()->getLib()->println(sqrt(sq(currentReading.x)+sq(currentReading.y)+sq(currentReading.z)));
  OLED::getInstance()->getLib()->print(currentDateTime.month);
  OLED::getInstance()->getLib()->print("/");
  OLED::getInstance()->getLib()->print(currentDateTime.day);
  OLED::getInstance()->getLib()->print("/");
  OLED::getInstance()->getLib()->println(currentDateTime.year);
  OLED::getInstance()->getLib()->println("<3");
  OLED::getInstance()->getLib()->print(currentDateTime.hour);
  OLED::getInstance()->getLib()->print(":");
  OLED::getInstance()->getLib()->print(currentDateTime.minute);
  OLED::getInstance()->getLib()->print(":");
  OLED::getInstance()->getLib()->println(currentDateTime.second);
  OLED::getInstance()->getLib()->println(ADXL::getInstance()->getLib()->isInactivityAc());
  OLED::getInstance()->getLib()->display();
  delay(100);
  OLED::getInstance()->getLib()->clear(PAGE);
  OLED::getInstance()->getLib()->setCursor(0,0);
}

void loop() {
    printScreen();
}