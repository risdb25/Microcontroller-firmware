#include <Arduino.h>
#include <SensorModule.h>
#include <Display.h>
/*Libraries included via project 'lib' folder:
* GxEPD
* esp32-micro-sdcard
*/

//Sleep variables
#define uS_TO_S_FACTOR 1000000 // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP 5        // Time ESP32 will go to sleep (in seconds)

//generic sensor configuration method?

SensorModule sensorModule;

void setup() 
{
  Serial.begin(115200);
  delay(500);

  //displays home page showing Dandelion logo & wifi connection status.
  Display d;
  //d.setupDisplay();

  //connect to wifi
  // WiFiConnection w;
  // w.connectToWifi(); -- TO DO: needs placed in a try..catch to allow for wifi connection to fail but not cause crash.

  //Initialise sensors then take readings
  sensorModule.initialise();
  delay(2000);
  sensorModule.getReadings();

  //convert to JSON - handled elsewhere

  //store on SD card - handled elsewhere

  //send readings - handled elsewhere

  //Confirm they have been sent on SD card (wifi not disconnected)

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() 
{}