#include "SensorModule.h"
#include <TSL2591.h>
#include <BME280.h>
#include <DS18B20.h>
#include <TGSMeter.h>
// #include <PHSensor.h>

/*In this class, readings are taken from each sensor, with the values returned stored in a map.
* the key-value pair in the map is String-float where string is the name of the type of measurement being recorded and 
* float is the measurement value itself. When all readings have been taken, the map is sent as an argument to the 
* DataTransformation class.
*/

//Derived sensor sub-class instances
TSL2591 luminositySensor;
BME280 multiPurposeSensor;
DS18B20 substrateTemperatureSensor;
TGSMeter tgsMeter;
// PHSensor pHSensor;

//Map for storing readings and the name of measurement type
std::map <String, float> readings;

//DataTransformation instance variable to access the serialise method it provides.
DataTransformation dt;

void SensorModule::initialise()
{
    luminositySensor.initialise();
    multiPurposeSensor.initialise();
    // //initialise water level sensor
    // tgsMeter.initialise();

    // substrateTemperatureSensor.initialise();
    //intialise humidity sensor
    //initialise moisture sensor

    // pHSensor.initialise();
}

float SensorModule::getReadings()
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

    // //read water level
    // readings["electrical conductivity"] = tgsMeter.getReadings();

    // // readings["substrate temperature"] = substrateTemperatureSensor.getReadings();

    // pHSensor.getReadings();

    delay(500);
    dt.serialise(readings);

    return 0;
}