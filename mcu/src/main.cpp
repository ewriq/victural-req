
#include <Arduino.h>
#include "wifi.h"
#include "http.h"
#include <ArduinoJson.h>
#include "globals.h"

const char *WIFI_SSID = "ewriq";
const char *WIFI_PASS = "f9663ddc";


JsonDocument doc;

void setup()
{
  Serial.begin(500000);
  delay(1000);

  doc["code"] = 200;
  doc["data"] = "Start";

  serializeJson(doc, Serial);
  Serial.println();

  connectToWiFi(WIFI_SSID, WIFI_PASS, 10000);
}

void loop()
{
  ensureWiFiConnected(WIFI_SSID, WIFI_PASS);

  int status;

  if (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n');

    String getResp = httpGET(input, status);

    printResponse(getResp, status);
  }
}
