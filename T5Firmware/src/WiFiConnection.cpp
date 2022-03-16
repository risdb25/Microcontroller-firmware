#include <WiFiConnection.h>

MicroSDCardOperations cardOperation;
extern DynamicJsonDocument configDoc; //global variable declared in main.cpp

String getTime();

void WiFiConnection::connectToWiFi()
{
    /*In this method, the wifi SSID and Password are read in from the configDoc file, which is a Json object that contains the config
    * information as stored on the MicroSD card. If the wifi connection after 8 seconds of trying is successful, the wifi logo on the display
    * is changed from disconnected to connected.
    */
    WiFiClient client;
    const char* ssid = configDoc["wifiCredentials"][0];
    const char* password = configDoc["wifiCredentials"][1];

    WiFi.begin(ssid, password);
    delay(8000);
    if(WiFi.status() == WL_CONNECTED)
    {
        Display display;
        display.updateWiFiIcon(true);
    }
}

void WiFiConnection::sendDataToServer(DynamicJsonDocument& doc)
{
    /*In this method, sensor readings are passed in as a parameter in the form of a JSON object. The JSON doc is converted
    * to a character array and sent using the Arduino WiFiClient class, after checking that the WiFi is connected and that we can reach
    * the required server. The current time is also retrieved and appended to the JSON document in this method.
    * The details of the server are read in from the global configDoc object. If we establish that WiFi connection is good,
    * the next check is whether there exists an "unsent" file on the MicroSD card. This file is created and populated with data while there has not been a 
    * connection established. If the file exists, these readings are dealt with first.
    */
    char jsonString[256]; //used to store converted JSON object in.
    String time = getTime(); //internal method returns time as String.
    Serial.println(time); //for testing purposes.
    doc["time"] = time; //append time to JSON object.
    
    serializeJson(doc, jsonString); //convert from JSON to character array.

    Serial.println(jsonString); //for testing purposes only.
    
    const char* host = configDoc["serverDetails"][0];
    uint16_t port = configDoc["serverDetails"][1];
    WiFiClient client;
    if(WiFi.status() == WL_CONNECTED)
    {
        //call MicroSDCardOperation method to check if unsent file exists, and if so they are sent.
        cardOperation.getUnsentReadings();

        //send data.
        if(client.connect(host, port))
        {
            client.print(jsonString);
            delay(4000);
            client.stop();
        }
        else
        {
            Serial.println("Couldn't connect to server, must store readings in unsent file");
            return;
        }

        //call MicroSDCardOperation method to store in READINGS.
        cardOperation.storeJsonOnFile(jsonString, "readings.txt");
    }
    else
    {
        /*There has been a problem connecting to Wi-Fi. The readings will be stored in the unsent.txt file, so
        * a call to the MicroSDCardOperation method for storing JSON on file is made, passing in the file name
        * as an argument.
        */
        cardOperation.storeJsonOnFile(jsonString, "unsent.txt");
        Serial.println("couldn't connect to wifi");
        Display display;
        display.updateWiFiIcon(false);
    }

}

void WiFiConnection::sendUnsentReadings(DynamicJsonDocument& doc)
{
    /*This method is called from within the getUnsentReadings method in the MicroSDCardOperations class. This method takes in a 
    * DynamicJsonDocument reference, serialises it to a character array, and sends it to the database over Wi-Fi.
    */

    char jsonString[256];
    serializeJsonPretty(doc, jsonString); //Converts JSON to String.
    
    WiFiClient client;
    WiFi.begin("BT-TZAT2F", "ReyrHg7Qqvea4c");
    delay(8000);
    if(WiFi.status() == WL_CONNECTED)
    {
        //send data
        if(client.connect("192.168.1.96", 21))
        {
            client.print(jsonString);
            delay(4000);
            client.stop();
        }
    }
    
    //call MicroSDCardOperation method to store in READINGS.
    cardOperation.storeJsonOnFile(jsonString, "readings.txt");
}

String getTime()
{
    const char* ntpServer = "pool.ntp.org";
    const long gmtOffset_sec = 0;
    const int daylightOffset_sec = 0;

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    if(!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return "";
    }
    char timeAsCharArray[32];
    std::strftime(timeAsCharArray, 32, "%A, %B %d %Y %H:%M:%S", &timeinfo);
    String timeAsString = timeAsCharArray;

    return timeAsString;
}