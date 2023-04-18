#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "Valar Dohaeris"
#define WIFI_PASS         "grasshopper"
#define APP_KEY           "62c61038-dd45-45f3-bdfa-5cc68c7fc4c2"
#define APP_SECRET        "6a170bc5-d971-4b85-8a11-edfd422fecb1-48319353-09da-485c-b8d7-89c262fd004e"
#define SWITCH1_ID         "61eaa57b5237d163c303c4e4"
#define SWITCH2_ID         "61ead1355237d163c303de09"
#define BAUD_RATE         9600

#include <Servo.h>

Servo servo;

bool onPowerState1(const String &deviceId, bool &state) {
 
  //Serial.printf("device %s turned %s\r\n", deviceId.c_str(), state?"on":"off");
  if (state) {
    Serial.printf("ON\r\n");
    lampOn();
  }
  else {
    lampOn();
    Serial.print("OFF\r\n");
  }

  return true; // indicate that callback handled correctly
}

bool onPowerState2(const String &deviceId, bool &state) {
 
  //Serial.printf("device %s turned %s\r\n", deviceId.c_str(), state?"on":"off");
  if (state) {
    Serial.printf("ON\r\n");
    changeColor();
  }
  else {
    changeColor();
    Serial.print("OFF\r\n");
  }

  return true; // indicate that callback handled correctly
}

void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  // add device to SinricPro
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH1_ID];
  SinricProSwitch& mySwitch2 = SinricPro[SWITCH2_ID];

  // set callback function to device
  mySwitch1.onPowerState(onPowerState1);
  mySwitch2.onPowerState(onPowerState2);

  // setup SinricPro
  SinricPro.onConnected([]() {
    Serial.printf("Connected to SinricPro\r\n");
  });
  SinricPro.onDisconnected([]() {
    Serial.printf("Disconnected from SinricPro\r\n");
  });

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void changeColor(){
  delay(100);
  servo.write(49);
  delay(1500);
  servo.write(0);
}


void lampOn(){
  delay(100);
  servo.write(49);
  delay(200);
  servo.write(0);
}

void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  servo.attach(2); //D4

  servo.write(0);

  delay(2000);
  setupWiFi();
  setupSinricPro();

}


void loop() {
  SinricPro.handle();
}
