#pragma once
#include <mySD.h>
#include <ArduinoJson.h>
#include <WifiConnection.h>

class MicroSDCardOperations
{
public:
    String readSDForWiFiCredenials();
    void storeJson(DynamicJsonDocument&);
};