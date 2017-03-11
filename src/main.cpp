#include <SSD1306.h>
#include <robotofont.h>
#include <Wire.h>
#include <Arduino.h>
#include <CCS811.h>

SSD1306 display(0x3c, D5, D6);

#define ADDR_CCS811      0x5A
#define WAKE_PIN  4
CCS811 sensor;
unsigned int TVOC = 0;
unsigned int CO2 = 0;


void init_oled(){
        display.init();
        display.displayOn();
        display.flipScreenVertically();
        display.setFont(Roboto_Medium_24);
}

void setup() {
        // put your setup code here, to run once:
        Serial.begin(115200);


        init_oled();
        display.clear();
        display.drawString(0, 0, "Hello\nWorld!");
        display.display();

        //air quality sensor setup
        if(!sensor.begin(uint8_t(ADDR_CCS811), uint8_t(WAKE_PIN))) {
                Serial.println("Initialization failed.");
        }
}

void loop() {
        delay(1000);

        sensor.getData();
        CO2 = sensor.readCO2();
        TVOC = sensor.readTVOC();

        Serial.println("CO2 " + String(CO2));
        Serial.println("TVOC " + String(TVOC));

        display.clear();
        display.drawString(0, 0, "CO2 "+String(CO2)+"\nVOC "+String(TVOC));
        display.display();


        if ((CO2 > 8192) || (TVOC > 1187)) {
                Serial.println("outside normal values #1");
                return;
        }

        if (CO2 < 10) {
                Serial.println("C02 is < 10");
                return;
        }

}
