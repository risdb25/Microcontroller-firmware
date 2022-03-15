#pragma once
#define LILYGO_T5_V213
#include <Arduino.h>
#include <boards.h>
#include <GxEPD.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

//Images:
#include <DandelionLogo.h>
#include <LossOfWifiIcon.h>

class Display
{
public:
    Display();
    void setupDisplay();
};


