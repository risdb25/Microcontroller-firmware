#pragma once
#include <DataTransformation.h>
#include <Arduino.h>
#include <map>
#include <math.h>

class SensorModule
{
public:
    virtual void initialise();
    virtual float getReadings();
    float getReadings(int);
};