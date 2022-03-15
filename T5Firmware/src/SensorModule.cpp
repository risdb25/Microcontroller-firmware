#include <SensorModule.h>
#include <TSL2591.h>
#include <BME280.h>

/*In this class, readings are taken from each sensor, with the values returned stored in a map.
* The key-value pair in the map is <String-float> where String value is the name of the type of measurement being recorded, and 
* the float value is the measurement itself. When all readings have been taken, the map is sent as an argument to the appropriate 
* method within the DataTransformation class for further processing.
*/

//Derived sensor sub-class instances
TSL2591 luminositySensor;
BME280 multiPurposeSensor;

//Map for storing readings and the name of measurement type
std::map <String, float> readings;

//DataTransformation instance variable to access the serialise method it provides.
DataTransformation dataTransformation;

void SensorModule::initialise()
{
    luminositySensor.initialise();
    multiPurposeSensor.initialise();
}

float SensorModule::getReadings()
{
    readings["luminosity"] = luminositySensor.getReadings();
    
    delay(1000);

    readings["temperature"] = multiPurposeSensor.getReadings(0);
    readings["pressure"] = multiPurposeSensor.getReadings(1);
    readings["altitude"] = multiPurposeSensor.getReadings(2);
    readings["humidity"] = multiPurposeSensor.getReadings(3);

    delay(1000);

    dataTransformation.serialise(readings);

    return 0;
}