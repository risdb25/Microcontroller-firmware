/*
***** OLD ATTEMPT USING SPIClass LIBRARY.
IT REGISTERS THE SD CARD EXISTS BUT THE FUNCTIONS FOR
READING AND WRITING DATA FROM AND TO THE CARD IS LACKING.
USING DIFFERENT LIBRARY ABOVE INSTEAD.
*/

// #include <Arduino.h>
// #include <SD.h>
// #include <SPI.h>
// SPIClass sdSPI(VSPI);

// #define SDCARD_CS 13
// #define SDCARD_CLK 14
// #define SDCARD_MOSI 15
// #define SDCARD_MISO 2

// void setup()
// {
//     Serial.begin(115200);
//     sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);

//     if (!SD.begin(SDCARD_CS, sdSPI)) 
//     {
//         Serial.println("SDCard init fail");

//     } 
//     else 
//     {
//         Serial.println("SDCard init pass");
//         SD.mkdir("test");
//         //Serial.println(didItWork);
//     }

// }

// void loop()
// {

// }