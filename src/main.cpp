#include <Arduino.h>
//#include <MD5.h>
#include "../lib/ArduinoMD5/MD5.h"

String buffer = "";
const String padding = "<->";
const String beginPadding = "<^|BEGIN_DATA|>";
const String endPadding = "<|END_DATA|$>";
const String infoPaddingBegin = "<^|BEGIN_INFO|>";
const String infoPaddingEnd = "<|END_INFO|$>";
const String opPaddingBegin = "<^|BEGIN_OPCODE|>";
const String opPaddingEnd = "<|END_OPCODE|$>";
const String hashPaddingBegin = "<^|BEGIN_HASH|#>";
const String hashPaddingEnd = "<#|END_HASH|$>";
int loopCount = 0;

String formatOPCode(int opCode) {
    String status = "";
    status += opPaddingBegin;
    status += opCode;
    status += opPaddingEnd;
    return status;
}

/**
 * @brief Collect all analog data and add them to the buffer
 */
String collectAllData() {
    String data = "";
    int analogPins[] = {analogRead(A0), analogRead(A1)};
    data += beginPadding;
    int analogPinArrSize = sizeof(analogPins) / sizeof(analogPins[0]);
    for (int i = 0; i < analogPinArrSize; i++) {
        data += "ANALOG_PIN_A";
        data += i;
        data += ":";
        data += analogPins[i];
        // only add padding if not last element
        if (i != analogPinArrSize - 1) {
            data += padding;
        }
    }
    data += endPadding;
    return data;
}

/**
 * @brief format the info data
 * @param info{String} the info data
 * @return the formatted info data
 */
String formatInfo(String info) {
    String returnInfo = "";
    returnInfo += infoPaddingBegin;
    returnInfo += info;
    returnInfo += infoPaddingEnd;
    return returnInfo;
}


/**
 * @brief Hash the buffer using MD5 and return the hash
 * @return String
 */
String hashData() {
    String data = "";
    char char_array[buffer.length() + 1];
    strcpy(char_array, buffer.c_str());
    unsigned char *hash = MD5::make_hash(char_array);
    char *md5str = MD5::make_digest(hash, 16);
    // add padding
    data += hashPaddingBegin;
    data += md5str;
    data += hashPaddingEnd;
    return data;
}

/**
 * @brief Combine the hash with the buffer
 * @param status{int} 0 = DATA, 1 = INFO
 * @param info{String} the info data
 */
void prepBuffer(int opCode, String info = "NO_INFO_PROVIDED") {
    // clear buffer
    buffer = "";
    if (opCode == 0) {
        delay(10);
        buffer += formatOPCode(0);
        buffer += collectAllData();
        String hash = hashData();
        buffer = hash + buffer;
    } else if (opCode == 1) {
        delay(10);
        buffer += formatOPCode(1);
        buffer += formatInfo(info);
        String hash = hashData();
        buffer = hash+ buffer;
    }

}

/**
 * @brief Send the buffer to the serial port
 */
void sendBuffer() {
    Serial.println(buffer);
    buffer = "";
    delay(10);
}

/**
 * @brief Call the prepBuffer and sendBuffer functions to send data
 */
void sendData() {
    prepBuffer(0);
    sendBuffer();
    delay(10);
}

/**
 * @brief Call the prepBuffer and sendBuffer functions to send info
 */
void sendInfo(String info) {
    prepBuffer(1, info);
    sendBuffer();
    delay(10);
}

/**
 * @brief cycle the LED on a pin
 * @param pin
 * @param delayTime
 */
void cycleLED(int pin, int delayTime) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
}

/**
 * @brief reset the Arduino
 */
void (*resetFunc)(void) = 0;

void setup() {
    Serial.begin(115200);
    sendInfo("STARTING");
    pinMode(12, OUTPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void loop() {
    sendData();
    cycleLED(12, 100);
    delay(3000);
    if (loopCount >= 10) {
        sendInfo("RESET");
        resetFunc();
    }
    loopCount++;
}