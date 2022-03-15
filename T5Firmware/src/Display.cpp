#include <Display.h>

 GxIO_Class io(SPI,  EPD_CS, EPD_DC,  EPD_RSET);
 GxEPD_Class  display(io, EPD_RSET, EPD_BUSY);

Display::Display()
{

}

void Display::setupDisplay()
{
    delay(2000);

    display.init();
    display.setRotation(1); //Sets rotation to landscape, where the bottom of the display == side that the buttons are on.

    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(100, 0, DandelionLogo, 50, 22, GxEPD_BLACK);
    display.drawBitmap(0, 0, LossOfWifiIcon, 30, 22, GxEPD_BLACK);
    display.update();
}