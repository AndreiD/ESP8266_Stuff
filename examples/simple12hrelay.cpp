


; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:esp01_1m]
platform = espressif8266
board = d1
framework = arduino
board_build.f_cpu = 16000000L
board_build.clock_source = 1
monitor_speed = 115200
upload_speed = 921600






#include <Arduino.h>

#define switchPin1 D7
#define switchPin2 D6
#define BAUDRATE 115200

#define relayPin D2
#define relayPin2 D3

long runtime = 0;
int cycleDuration = 0;
long dimTime = 1L * 60L * 60L * 1000L; // 1h
// long dimTime = 1000; // 1h
long dayDuration = 24L * 60L * 60L * 1000L;
// long dayDuration = 24000;

void turnDimRelayOn();
void turnDimRelayOff();
void turnFullRelayOn();
void turnFullRelayOff();

void updateState(int switchState1, int switchState2)
{
  if (switchState1 == HIGH && switchState2 == HIGH)
  {
    cycleDuration = 8L * 60L * 60L * 1000L; // hours
    // cycleDuration = 8000; // hours
  }
  if (switchState1 == LOW && switchState2 == HIGH)
  {
    cycleDuration = 6L * 60L * 60L * 1000L; // hours
    // cycleDuration = 6000; // hours
  }
  if (switchState1 == HIGH && switchState2 == LOW)
  {
    cycleDuration = 12L * 60L * 60L * 1000L; // hours
    // cycleDuration = 12000; // hours
  }
}

void setup()
{
  delay(500);
  // Initialize Serial for debuging purposes.
  Serial.begin(BAUDRATE);
  while (!Serial)
    ;
  Serial.println();
  Serial.println(">>> Simple12HRelay Version 0.2 <<<");

  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);

  pinMode(relayPin, OUTPUT);
  pinMode(relayPin2, OUTPUT);

  turnDimRelayOff();
  turnFullRelayOff();
}

void loop()
{
  int switchState1 = digitalRead(switchPin1);
  int switchState2 = digitalRead(switchPin2);

  updateState(switchState1, switchState2);

  runtime = runtime + 1000;
  delay(1000); // Print every second

  if (runtime > dayDuration)
  {
    Serial.println("===== NEW CYCLE BEGINS =====");
    runtime = 0;
  }

  if (runtime < cycleDuration)
  {
    turnDimRelayOn(); // dim relay is always on in the cycle
    // should be full relay on?
    if (runtime > dimTime && runtime < (cycleDuration - dimTime))
    {
      turnFullRelayOn();
    }
    else
    {
      turnFullRelayOff();
    }
  }
  else
  {
    if (runtime % 60000 == 0)
    {
      Serial.printf("cycleDuration: %d\n", cycleDuration);
      Serial.println("zzZzzzZzzz.....");
    }
    turnDimRelayOff();
    turnFullRelayOff();
  }
}

//------- DIM RELAY PIN D3
void turnDimRelayOn()
{
  digitalWrite(relayPin2, LOW);
}

void turnDimRelayOff()
{
  digitalWrite(relayPin2, HIGH);
}

//------- FULL RELAY PIN D2
void turnFullRelayOn()
{
  digitalWrite(relayPin, LOW);
}

void turnFullRelayOff()
{
  digitalWrite(relayPin, HIGH);
}

