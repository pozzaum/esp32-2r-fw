#include "serial_client.h"
#include <stdlib.h>

SerialClient::SerialClient()
    : _rxBuffer(""),
      _targetShoulder(0),
      _targetElbow(0),
      _newCommand(false),
      _started(false) {}

void SerialClient::begin(unsigned long baudrate) {
    Serial.begin(baudrate);
    _started = true;

    Serial.println("[SERIAL] Serial iniciada.");
    Serial.println("[SERIAL] Envie dois alvos separados por espaco ou virgula.");
    Serial.println("[SERIAL] Ex.: 1000 -500");
}

void SerialClient::update() {
    if (!_started) {
        return;
    }

    while (Serial.available()) {
        char c = static_cast<char>(Serial.read());

        if (c == '\r') {
            continue;
        }

        if (c == '\n') {
            if (_rxBuffer.length() > 0) {
                long shoulder = 0;
                long elbow = 0;

                if (parseMessage(_rxBuffer, shoulder, elbow)) {
                    _targetShoulder = shoulder;
                    _targetElbow = elbow;
                    _newCommand = true;

                    Serial.print("[SERIAL] Comando recebido -> shoulder: ");
                    Serial.print(_targetShoulder);
                    Serial.print(" | elbow: ");
                    Serial.println(_targetElbow);
                } else {
                    Serial.print("[SERIAL] Mensagem invalida: ");
                    Serial.println(_rxBuffer);
                }
            }

            _rxBuffer = "";
        } else {
            _rxBuffer += c;

            if (_rxBuffer.length() > 64) {
                _rxBuffer = "";
                Serial.println("[SERIAL] Buffer excedeu limite. Limpando.");
            }
        }
    }
}

bool SerialClient::hasNewCommand() const {
    return _newCommand;
}

void SerialClient::clearNewCommandFlag() {
    _newCommand = false;
}

long SerialClient::getTargetShoulder() const {
    return _targetShoulder;
}

long SerialClient::getTargetElbow() const {
    return _targetElbow;
}

bool SerialClient::parseMessage(const String& message, long& targetShoulder, long& targetElbow) {
    String msg = message;
    msg.trim();

    if (msg.length() == 0) {
        return false;
    }

    int sepIndex = msg.indexOf(' ');
    if (sepIndex < 0) {
        sepIndex = msg.indexOf(',');
    }

    if (sepIndex < 0) {
        return false;
    }

    String shoulderStr = msg.substring(0, sepIndex);
    String elbowStr = msg.substring(sepIndex + 1);

    shoulderStr.trim();
    elbowStr.trim();

    if (shoulderStr.length() == 0 || elbowStr.length() == 0) {
        return false;
    }

    char* endPtr1 = nullptr;
    char* endPtr2 = nullptr;

    targetShoulder = strtol(shoulderStr.c_str(), &endPtr1, 10);
    targetElbow = strtol(elbowStr.c_str(), &endPtr2, 10);

    if (*endPtr1 != '\0' || *endPtr2 != '\0') {
        return false;
    }

    return true;
}