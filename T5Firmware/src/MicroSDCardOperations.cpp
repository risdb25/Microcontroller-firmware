#include <MicroSDCardOperations.h>


#define SDCARD_CS 13
#define SDCARD_MOSI 15
#define SDCARD_MISO 2
#define SDCARD_CLK 14

void MicroSDCardOperations::storeJsonOnFile(String jsonString, const char* fileName)
{
    /*This method is called from either the sendDataToServer() or sendUnsentReadings() method in the 
    * WiFiConnecion class. In this method, we take in as a parameter the JSON data as a String, and 
    * the name of the file for the data to be written to. The String format of the JSON data is then
    * written to the file.
    */
    delay(500);
    SD.begin(SDCARD_CS, SDCARD_MOSI, SDCARD_MISO, SDCARD_CLK);
    File file = SD.open(fileName, FILE_WRITE);

    if(file)
    {
        file.println(jsonString);
        file.close();
        Serial.println("Readings stored successfully");
    }
    else
    {
        Serial.println("Error printing to SD card");
    }

}

void MicroSDCardOperations::getUnsentReadings()
{
    /*This method is called from the WifiConnection class before the latest readings are attempted to be sent to the database.
    * The method checks if the unsent.txt file has been created, and if so, reads in all the data from it. When the Json strings are read in
    * from the file, they are each deserialised into to a DynamicJsonDocument and then sent to the appropriate method in the WifiConnection class. The reason
    * they are formatted back to being Json again is to ensure the integrity. If just sending the String straight from file, the closing curly brace is missing due to the
    * way in which each individual Json object is read in. At the end of the method, after all the unsent readings have been sent, the file can be deleted.
    */

    delay(500);
    SD.begin(SDCARD_CS, SDCARD_MOSI, SDCARD_MISO, SDCARD_CLK);
    int i = 0;
    if(SD.exists("unsent.txt"))
    {
        File file = SD.open("unsent.txt");
        DynamicJsonDocument doc(256);
        String readings;
        WiFiConnection wiFiOperation;

        while(file.available())
            {
                readings = file.readStringUntil('}'); //when the end of a JSON string is reached
                deserializeJson(doc, readings); //convert String to JSON
                wiFiOperation.sendUnsentReadings(doc); //send it to the database
                Serial.printf("Number of unsent readings passed = %d\n", ++i);
                delay(2000);
            }

        file.close();
        SD.remove("unsent.txt");
        Serial.println("unsent.txt deleted");
    }
    else
    {
        Serial.println("No unsent readings stored on the SD card.");
    }

}

DynamicJsonDocument MicroSDCardOperations::getConfigData()
{
    /*In this method, the config file is read in from the MicroSD card. It is stored as a String on file
    * so after it has been read in, it is converted back to being a true JSON object and returned from the method
    * back to main.cpp where this method was called from.
    */
    delay(500);
    SD.begin(SDCARD_CS, SDCARD_MOSI, SDCARD_MISO, SDCARD_CLK);
    File file = SD.open("config.txt");
    String data; //used to store the String read in from the config file on MicroSD card
    DynamicJsonDocument configData(256); //the Json doc that will be passed back to main

    data = file.readString();
    deserializeJson(configData, data);
    
    return configData;
}