#include <Arduino.h>
#include <ADXL.h>
#include <EEPROM.h>
#include <MCP.h>
#include <Wire.h>

EEPROM eeprom;
ADXL acceler;
MCP rtclock;

void setupI2C(){
  Wire.begin(); //join i2c bus
  Wire.setClock(100000);
}

void setupSPI(){
  
}

void setup() {
     /*
   * Configure all buses
   */
  setupI2C();
  //setupSPI();

  /**
  * Initialize the EEPROM
  */
  eeprom.setupEEPROM();

  /**
   * Configure the ADXL345
   */
  acceler.setupADXL345();

  /**
   * Initialize configuration data for the RTC. Modify
   * the contents of the initConfig object such that the
   * RTC will begin with the correct values
   */
  DateTime initConfig;
  rtclock.setupRTC(&initConfig);

  Serial.begin(9600);
}

Accel currentReading;
DateTime currentDateTime;

void loop() {
    /**
   * Test #1: Try to read from the ADXL345 and
   * print out the results
   */
  
  /*
  acceler.readADXL(&currentReading);

  Serial.print(currentReading.x);
  Serial.print("\t");
  Serial.print(currentReading.y);
  Serial.print("\t");
  Serial.println(currentReading.z);
  */

  /**
   * Test #2: Try to read out the time of day and
   * print out the results
   */

  /*
   rtclock.readRTC(&currentDateTime);
   Serial.print(currentDateTime.month);
   Serial.print("/");
   Serial.print(currentDateTime.day);
   Serial.print("/");
   Serial.print(currentDateTime.year);
   Serial.print("\t");
   Serial.print(currentDateTime.hour);
   Serial.print(":");
   Serial.print(currentDateTime.minute);
   Serial.print(":");
   Serial.println(currentDateTime.second);
  
  */

   /**
    * Test #3: Try to write and read back some
    * random data
    */
/*
   
    uint16_t array[5];
    for(int i=0;i<5;i++)
    {
      array[i]=random();
    }
    eeprom.writeDataToEEPROM(array,5);

    uint16_t buffer[5];

	eeprom.readDataFromEEPROM(buffer,5);

  for(int i = 0; i < 5; i ++){
  Serial.println(long(array[i]));
  Serial.println(long(buffer[i]));
  }
	
	bool testPass = true;
	for(int i=0;i<5;i++)
	{
		if(buffer[i]!=array[i])
		{
			testPass=false;
		}
	}
	
	if(testPass)
	{
		Serial.println("EEPROM Test Passed.");
	}
	else
	{
		Serial.println("EEPROM Test Failed.");
	}
*/
}