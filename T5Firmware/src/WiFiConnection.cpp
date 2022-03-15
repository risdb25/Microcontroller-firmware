#include <WiFiConnection.h>

MicroSDCardOperations sd;

const char* m_ssid;
const char* m_password;

/*TODO: CURRENTLY THIS CLASS READS IN THE DATA DIRECTLY FROM THE SD CARD, BUT I NEED TO CHANGE THIS
* SO THAT THE WIFI CREDENTIALS ARE STORED IN ONE GENERAL CONFIG FILE AND READ INTO A STRING UPON THE FIRMWARE
BOOTING UP. Once this change has been implemented, the BELOW METHOD can be CHANGED to instead obtain the 
information from this string
*/
void WiFiConnection::connectToWifi()
{
    /*Use instance of our MicroSDCardOperations class to
    * retrieve the credentials from the creden file on the SD card.
    * Once the SD method has returned the entire contents of the file, 
    * this method then gets the index of the space separating the ssid and password,
    * then uses substring function twice -- once until the index and once from the index where the space is,
    * in order to obtain the ssid and password from the file. Lastly, any preceding or proceeding spaces are
    * cleared using trim(), before the class const char* variables are ready to be populated. This is the format
    * that the WiFi.begin() function requires.
    */
    String line, ssid, password; 
    line = sd.readSDForWiFiCredenials();

    //find index where space is, use this info to define ssid and password
    int indexOfSpace = line.indexOf(' ');
    ssid = line.substring(0, indexOfSpace);
    password = line.substring(indexOfSpace);

    //remove any leading and trailing whitespace
    ssid.trim();
    password.trim();

    //convert to const char* for wifi.begin()
    m_ssid = ssid.c_str();
    m_password = password.c_str();

    delay(1000);

    Serial.printf("Connecting to %s", m_ssid);
    WiFi.begin(m_ssid, m_password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println(".");
    }
    Serial.println("Connected");

    //TODO: update wifi connection symbol on display
}

void WiFiConnection::sendDataToServer(String jsonString)
{
    WiFiClient client;
    if(WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin("BT-TZAT2F", "ReyrHg7Qqvea4c"); //read credentials from config string taken from SD card.
    }

    if(WiFi.status() == WL_CONNECTED)
    {
        if(client.connect("192.168.1.96", 21)) //change to Dandelion details
        {
            Serial.println("found FTP server");
            client.print(jsonString);
            delay(2000);
            client.stop();
        }
    }
    else
    {
        //do something about the connection
        Serial.println("Wifi connection unavailable");
    }

}