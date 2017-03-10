#include <SSD1306.h>
#include <robotofont.h>
#include <Wire.h>
#include <Arduino.h>

SSD1306 display(0x3c, D1, D2);


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


}

void loop() {
        Serial.println ("I2C scanner. Scanning ...");
        byte count = 0;

        Wire.begin();
        for (byte i = 8; i < 120; i++)
        {
                Wire.beginTransmission (i);
                if (Wire.endTransmission () == 0)
                {
                        Serial.print ("Found address: ");
                        Serial.print (i, DEC);
                        Serial.print (" (0x");
                        Serial.print (i, HEX);
                        Serial.println (")");
                        count++;
                        delay (1); // maybe unneeded?
                } // end of good response
        } // end of for loop

        Serial.print (count, DEC);
        Serial.println (" device(s).");
        delay(2500);

}
