#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

bool connectToWiFi(const char* ssid, const char* pass, unsigned long timeoutMs = 15000);
void ensureWiFiConnected(const char* ssid, const char* pass, unsigned long checkInterval = 5000);

#endif
