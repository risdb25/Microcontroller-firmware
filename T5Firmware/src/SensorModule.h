#pragma once
#include <Arduino.h>
#include <map>
#include <DataTransformation.h>

class SensorModule
{
public:
    virtual void initialise();
    virtual float getReadings(); 
    float getReadings(int);
};