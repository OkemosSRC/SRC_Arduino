#include <Arduino.h>
#include "MD5.h"

String buffer = "";
String padding = "<->";
String endPadding = "<||$";
String beginPadding = "^||>";
String hashPaddingBegin = "<|#>";
String hashPaddingEnd = "<|#>";

void setup() {
    // set up the LED on pin 12
    pinMode(12, OUTPUT);
    // set analog input pin 0 as input
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    // serial port for debugging
    Serial.begin(115200);
}


void collectData(){
    int analogValue = analogRead(A0);
    int analogValue2 = analogRead(A1);
    buffer += beginPadding;
    buffer += "ANALOG_PIN_A0";
    buffer += ":";
    buffer += analogValue;
    buffer += padding;
    buffer += "ANALOG_PIN_A1";
    buffer += ":";
    buffer += analogValue2;
    buffer += endPadding;
}


void loop() {
    delay(3000);
    collectData();
    char char_array[buffer.length() + 1];
    strcpy(char_array, buffer.c_str());
    unsigned char* hash=MD5::make_hash(char_array);
    char *md5str = MD5::make_digest(hash, 16);
    buffer += hashPaddingBegin;
    buffer += md5str;
    buffer += hashPaddingEnd;
    Serial.println(buffer);
    buffer = "";
    free(md5str);
    //free(hash);
    // blink the LED on pin 12
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
}