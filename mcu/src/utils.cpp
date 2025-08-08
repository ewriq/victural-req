#include <base64.h>

String encodeBase64(const String &input) {
    return base64::encode(input);
}   