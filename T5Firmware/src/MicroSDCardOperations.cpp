#include <MicroSDCardOperations.h>

/*In this class, any interactions necessary with the MicroSD card inserted into the T5's module
* are handled. This includes reading in the config file and writing the Json-ified sensor readings
*/

#define SDCARD_CS 13
#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_CLK 14

/*Meeting with Brian on 23/02/22 we said that we should just have one config file on the SD card
* that has on it Wi-Fi credentials as well as the values needed for the configation of sensors that need it, 
* so we just need to read in this config file and store it in a map if the config file is in Json, which it may as well be, e.g.:
* {
    "credentials" : {SSID = bt, PASSWORD = password123},
    "sensor1Calibration" : pH = 7
}.. or something.
*/

String MicroSDCardOperations::readSDForWiFiCredenials()
{
    SD.begin(SDCARD_CS, SDCARD_MOSI, SDCARD_MISO, SDCARD_CLK);
    File credentials = SD.open("/creden.txt");
    
    String line = credentials.readString();

    credentials.read();
    credentials.close();
    
    return line;
}

void MicroSDCardOperations::storeJson(DynamicJsonDocument& doc)
{
    /*In this method, the reference to the Json object passed as an argument to the method is 
    * converted to a char array in order for the SD library to handle writing the data to the
    * card - the library cannot handle being passed a Json object directly and so it must be 
    * converted. Once the data has been stored on the card, the char array version of the data
    * is then passed to the appropriate method in the WiFiConnection class to be sent to 
    * and stored on the database.
    */

   WiFiConnection wiFiConnection;

    SD.begin(SDCARD_CS, SDCARD_MOSI, SDCARD_MISO, SDCARD_CLK);
    File file = SD.open("readings.txt", FILE_WRITE);
    char output[256];
    serializeJsonPretty(doc, output);
    
    if(file)
    {
        file.println(output);
        file.close();
    }
    else
    {
        Serial.println("Error printing to SD card");
    }

    wiFiConnection.sendDataToServer(output);
}