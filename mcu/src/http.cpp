#include "http.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "globals.h"
#include "utils.h"

String httpGET(const String &url, int &StatusCode, unsigned long) {
    StatusCode = -1;
    if (WiFi.status() != WL_CONNECTED) {
        doc["code"] = 502;
        doc["data"] = "WiFi not connected";
        serializeJson(doc, Serial);
        return "";
    }

    WiFiClient client;
    HTTPClient http;
    http.setTimeout(30000);
    http.begin(client, url);

    StatusCode = http.GET();

    yield();  // Önemli: watchdog'u besle

    String payload = "";

    if (StatusCode > 0) {
        payload = http.getString();
        yield();
        doc["code"] = 200;
        doc["data"] = "HTTP request successful";
        serializeJson(doc, Serial);
    } else {
        doc["code"] = 502;
        doc["data"] = "HTTP error: " + http.errorToString(StatusCode);
        serializeJson(doc, Serial);
    }
    
    http.end();
    return payload;
}

void printResponse(const String &resp, int statusCode) {
    doc["code"] = (statusCode == 200) ? 200 : 502;
    doc["data"] = "HTTP Status: " + String(statusCode);
    serializeJson(doc, Serial);
    Serial.println();
    yield();

    if (resp.length() > 0) {
        String encoded = encodeBase64(resp);
        doc.clear();
        doc["code"] = 200;
        doc["data"] = encoded;
        serializeJson(doc, Serial);
        Serial.println();
        yield();
    } else {
        doc.clear();
        doc["code"] = 502;
        doc["data"] = "Response is empty";
        serializeJson(doc, Serial);
        Serial.println();
        yield();
    }
}
