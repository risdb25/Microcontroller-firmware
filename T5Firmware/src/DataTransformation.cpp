#include <DataTransformation.h>

/*In this class, the map built in the SensorModule class which contains sensor readings is 
* serialised to Json using the ArduinoJSON library. Once the map has been serialised, the Json
* object is passed to the relevant method in the MicroSDCardOperations class for storage.
*/

MicroSDCardOperations cardOperation;

using namespace std; //needed otherwise a double scope operator is required in the iterator definition.

void DataTransformation::serialise(std::map <String, float> p_readings)
{
    //In this method, an interator is used to extract each key-value pair that's stored in the map.

    DynamicJsonDocument doc(256);
    std::map<String, float>::iterator itr;

    for (itr = p_readings.begin(); itr != p_readings.end(); ++itr)
    {
        doc[itr->first] = itr->second;
    }

    serializeJsonPretty(doc, Serial); //for testing purposes

    cardOperation.storeJson(doc);
}