#pragma once
#include <ArduinoJson.h>
#include <map>
#include <iterator>
#include <MicroSDCardOperations.h>

class DataTransformation
{
public:
    void serialise(std::map <String, float> readings);
};