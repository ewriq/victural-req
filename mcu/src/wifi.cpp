#include "wifi.h"
#include <ArduinoJson.h>
#include "globals.h"
static unsigned long lastWiFiCheck = 0;

bool connectToWiFi(const char *ssid, const char *pass, unsigned long timeoutMs)
{
    if (WiFi.status() == WL_CONNECTED)
        return true;

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeoutMs) {
        delay(100);
    }

    if (WiFi.status() == WL_CONNECTED) {
        doc["code"] = 200;
        doc["data"] = WiFi.localIP().toString();
        serializeJson(doc, Serial);
        return true;
    }

    doc["code"] = 502;
    doc["data"] = "WiFi connection failed (timeout).";
    serializeJson(doc, Serial);
    return false;
}


void ensureWiFiConnected(const char *ssid, const char *pass, unsigned long checkInterval)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        unsigned long now = millis();
        if (now - lastWiFiCheck < checkInterval)
            return;
        lastWiFiCheck = now;

        doc["code"] = 502;
        doc["data"] = "Wifi error reconnection ...";

        serializeJson(doc, Serial);
        connectToWiFi(ssid, pass, 8000);
    }
}
