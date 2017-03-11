#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <CCS811.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Fonts/FreeSans12pt7b.h"
#define OLED_RESET 4


Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error ("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define WAKE_PIN  4  //not used.
#define ADDR      0x5A

CCS811 sensor;

unsigned int TVOC = 0;
unsigned int CO2 = 0;
int ledState = LOW;
unsigned int pTVOC = 0;
unsigned int pCO2 = 0;
unsigned int abs_v = 0;

void blink(){
        if (ledState == LOW) {
                ledState = HIGH;
        } else {
                ledState = LOW;
        }
        digitalWrite(LED_BUILTIN, ledState);
}

void setup()
{
        Serial.begin(9600);

        //sensor setup
        if(!sensor.begin(uint8_t(ADDR), uint8_t(WAKE_PIN))) {
                Serial.println("Initialization failed.");
        }

        //oled setup
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,22);
        display.setFont(&FreeSans12pt7b);

        pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
        sensor.getData();
        CO2 = sensor.readCO2();
        TVOC = sensor.readTVOC();


        if ((CO2 > 8192) || (TVOC > 1187)) {
                Serial.println("outside normal values #1");
                return;
        }

        if (CO2 < 350) {
                Serial.println("C02 is < 350");
                return;
        }

        display.clearDisplay();
        display.setCursor(0,22);

        if(CO2 > 1000) {
                blink();
        }else{
                digitalWrite(LED_BUILTIN, LOW);
        }

        if(CO2>pCO2) {
                abs_v = CO2 - pCO2;
        }else{
                abs_v = pCO2 - CO2;
        }

        Serial.println("CO2: "+ String(CO2)+ " pCO2:"+ String(pCO2) + " abs:" + String(abs_v));
        if(abs_v>35) {

                display.println("CO2 "+String(CO2));
                display.println("TVOC " + String(TVOC));
                display.display();
        }else{
                Serial.println("skipping...");
        }
        pCO2 = CO2;
        pTVOC = TVOC;

        delay(1000);

}
