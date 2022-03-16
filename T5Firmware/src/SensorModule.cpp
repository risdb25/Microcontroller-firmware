#include "SensorModule.h"
#include <TSL2591.h>
#include <BME280.h>
#include <DS18B20.h>
#include <TGSMeter.h>
#include <PHSensor.h>

/*In this class, readings are taken from each sensor, with the values returned stored in a map.
* The key-value pair in the map is String-float where string is the name of the type of measurement being recorded and 
* float is the measurement value itself. When all readings have been taken, the map is sent as an argument to the 
* DataTransformation class.
*/

//Derived sensor sub-class instances
TSL2591 luminositySensor;
BME280 multiPurposeSensor;
DS18B20 substrateTemperatureSensor;
TGSMeter tgsMeter;
PHSensor pHSensor;

//Map for storing readings and the name of measurement type
std::map <String, float> readings;

//DataTransformation instance variable to access the serialise method it provides.
DataTransformation dataTransformation;

/* The following method is currently called within this class, however it may instead be declared as a method in SensorModule.h and called from the SensorSelection.cpp class once 
* all readings have been taken. Currently unable to test readings being taken from all three levels, only one level is possible at this stage.
*/
void sendReadings();

void SensorModule::initialise(){} //virtual method so must be implemented, though it is not used in this class.
float SensorModule::getReadings(){return 0;} //virtual method so must be implemented, though it is not used in this class.

void SensorModule::initialiseSet1()
{
    luminositySensor.initialise();
    multiPurposeSensor.initialise();
    // //initialise water level sensor
    // tgsMeter.initialise();

}

void SensorModule::initialiseSet2()
{
    substrateTemperatureSensor.initialise();
    //intialise humidity sensor
    //initialise moisture sensor
}

void SensorModule::initialiseSet3()
{
    pHSensor.initialise();
}

void SensorModule::getReadingsSet1()
{
    readings["luminosity"] = luminositySensor.getReadings();
    delay(500);
    
    readings["temperature"] = multiPurposeSensor.getReadings(0);
    delay(500);
    readings["pressure"] = multiPurposeSensor.getReadings(1);
    delay(500);
    readings["altitude"] = multiPurposeSensor.getReadings(2);
    delay(500);
    readings["humidity"] = multiPurposeSensor.getReadings(3);

    // tgsMeter.getReadings();

    //get water level sensor readings

}

void SensorModule::getReadingsSet2()
{
    readings["substrate temp"] = substrateTemperatureSensor.getReadings();
    sendReadings(); //TESTING PURPOSES ONLY - REMOVE!!!!!
}

void getReadingsSet3()
{
    readings["pH"] = pHSensor.getReadings();
    sendReadings(); //could be changed to instead be called from SensorSelection.cpp
}

void sendReadings()
{
    dataTransformation.serialise(readings);
}