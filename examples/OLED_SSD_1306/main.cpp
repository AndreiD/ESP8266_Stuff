//remember to add the library esp8266-oled-ssd1306
#include <SSD1306.h>
#include <robotofont.h>


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

        display.drawString(0, 0, "First Line\nSecond...");
        display.display();

}

void loop() {
        //whatever

}
