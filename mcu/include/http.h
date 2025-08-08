#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <Arduino.h>

String httpGET(const String& url, int& outStatusCode, unsigned long timeoutMs = 10000);
String httpPOST(const String& url, const String& payload, const String& contentType, int& outStatusCode, unsigned long timeoutMs = 15000);
void printResponse(const String& resp, int code);

#endif
