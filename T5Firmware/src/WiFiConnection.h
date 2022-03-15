#pragma once
#include <WiFi.h>
#include <time.h>
#include <MicroSDCardOperations.h>

class WiFiConnection
{
public:
    void printLocalTime();
    void connectToWifi();
    void sendDataToServer(String);
};
