#include <Arduino.h>
#include <ADXL.hpp>
#include <EEPROM.hpp>
#include <Wire.h>
#include <OLED.hpp>
#include <RTC.hpp>
#include <avr/sleep.h>
#include <avr/power.h>
#include <STEPCOUNT.hpp>

#define ADXLINT1 0
#define ADXLINT2 1

static boolean justBooted = true;
static boolean brownOut = false;

  uint8_t EF_Global;
//------------------------
const uint8_t EF_ADXL = 0x01;
const uint8_t EF_EEPROM = 0x02;
const uint8_t EF_RTC = 0x03;
const uint8_t EF_OLED = 0x04;
const uint8_t EF_I2C = 0x05;

uint8_t TF_Global[5];
//------------------------
//First TF index
const uint8_t TF_ADXL_WATERMARK = 0x01;
const uint8_t TF_ADXL_DOUBLETAP = 0x02;
const uint8_t TF_ADXL_INACTIVITY = 0x03;
//Second TF index
const uint8_t TF_RTC_15MIN = 0x01;

RTC* rtc = RTC::getInstance();
EEPROM* eeprom = EEPROM::getInstance();
ADXL* adxl = ADXL::getInstance();
OLED* oled = OLED::getInstance();
STEPCOUNT* stepcnt = STEPCOUNT::getInstance();


void delayLoop()
{
  long startTime = millis();
  const long totalDelay = 5000;

  bool timeExpired = (millis() - startTime) > totalDelay;
  while (!timeExpired)
  {
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    delay(100);

    timeExpired = (millis() - startTime) > totalDelay;
  }
}

void setupI2C(){
  Wire.begin(); //join i2c bus
  Wire.setClock(400000);
}

void ADXL_ISR(){
  EF_Global |= EF_ADXL;
}

void EEPROM_ISR(){
  EF_Global |= EF_EEPROM;
}

void RTC_ISR(){

  EF_Global |= EF_RTC;
}

void sleep(){
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);

    //enable sleep mode by setting the sleep bit
    sleep_enable();

    //re-enable interrupts. If you do not, then you will never
    //awake from sleep...
    sei();

    //execute the sleep instruction and actually go to sleep
    sleep_cpu();

    //WAKE UP! First thing to do is disable sleep so we
    //don't do it again.
    sleep_disable();
}

void perifDisable(){
  power_all_enable();
  //power_timer0_enable();
  //power_usb_enable();
  //power_twi_enable();
}


void setup() {

  /**
   * Create an interrupt for ADXL on Digital Pin 1 (DOUBLETAP)
   */ 
  pinMode(1,INPUT);
  attachInterrupt(digitalPinToInterrupt(1), ADXL_ISR, RISING);

  pinMode(7,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), RTC_ISR, FALLING);
  /**
   * Create an interrupt for ADXL on Digital Pin 0 (Watermark and DATAREADY)
   */
  //pinMode(0,INPUT);
  //attachInterrupt(digitalPinToInterrupt(0), ADXL_ISR, RISING);

    /**
   * Initialize configuration data for the RTC. Modify
   * the contents of the initConfig object such that the
   * RTC will begin with the correct values
   */
  rtc->setupRTC();

  //CLKPR = _BV(CLKPCE);  // enable change of the clock prescaler
  //CLKPR = _BV(CLKPS0);  // divide frequency by 2

  perifDisable();

  pinMode(4,OUTPUT);
  /**
   * Temp function to prevent bricking
   */
  delayLoop();
     /*
   * Configure all buses
   */
  setupI2C();
  /**
  * Initialize the EEPROM
  */
  eeprom->setupEEPROM();
  /**
   * Configure the ADXL345
   */
  adxl->setupADXL345();
  /**
   * Configure the OLED
   */
  oled->setUpOLED();

  //rtc->setTimer(900,1);
}

Accel currentReading;
DateTime currentDateTime;
uint16_t totalSteps = 0;
int16_t* accelFifo = new int16_t[32];
uint8_t alarmtype;

void loop() {
    Serial.println(EF_Global);
    if(EF_Global != 0)
    {
      if(EF_Global == EF_ADXL){
        EF_Global &= ~EF_ADXL;

        uint8_t source = adxl->getLib()->getInterruptSource() & ~(0xDD);  //0xDD flag mask to prevent wrong source reads
        
        if(adxl->getLib()->triggered(source,ADXL345_WATERMARK)){
            //need to setup Watermark interrupt
            adxl->readFIFO(accelFifo, 32, &currentReading); 
            stepcnt->calculateSteps(accelFifo, &totalSteps);
        }
       
        if(adxl->getLib()->triggered(source, ADXL345_DOUBLE_TAP)){
          //display time, day and step count
            currentDateTime = *(rtc->getTime());
            oled->wakeup();
            oled->getLib()->clear(PAGE);
            oled->getLib()->setCursor(0,0);
            oled->getLib()->print(currentDateTime.month());
            oled->getLib()->print("/");
            oled->getLib()->println(currentDateTime.day());
            oled->getLib()->print(currentDateTime.hour());
            oled->getLib()->print(":");
            oled->getLib()->println(currentDateTime.minute());
            oled->getLib()->print(totalSteps);
            oled->getLib()->display();
            rtc->setTimer(5,0);
        }
      }

      if(EF_Global == EF_RTC){
          EF_Global &= ~EF_RTC;
          if(rtc->getLib()->isAlarm(0)){
            rtc->getLib()->clearAlarm(0);
            oled->getLib()->clear(PAGE);
            oled->getLib()->display();
            oled->getLib()->setCursor(0,0);
            oled->sleep();
          }
          else if(rtc->getLib()->isAlarm(1)){
            rtc->getLib()->clearAlarm(1);
            rtc->setTimer(900,1);
            Serial.println("ALARM2 POPPED");
            //save to EEPROM
          }
        }
    //put processor to sleep
    //sleep();  //need to pull MFP up to vcc using 10k resistor to properly wake up
    }

}