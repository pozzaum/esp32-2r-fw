#include "bt_client.h"

BtClient::BtClient()
    : _rxBuffer(""),
      _theta1(0.0f),
      _theta2(0.0f),
      _newCommand(false),
      _started(false) {}

bool BtClient::begin(const String& device_name) {
    if (_serialBT.begin(device_name)) {
        _started = true;
        Serial.println("[BT] Bluetooth Serial iniciado com sucesso.");
        Serial.print("[BT] Nome do dispositivo: ");
        Serial.println(device_name);
        return true;
    }

    Serial.println("[BT] Falha ao iniciar Bluetooth Serial.");
    return false;
}

void BtClient::update() {
    if (!_started) {
        return;
    }

    while (_serialBT.available()) {
        char c = static_cast<char>(_serialBT.read());

        if (c == '\r') {
            continue;
        }

        if (c == '\n') {
            if (_rxBuffer.length() > 0) {
                float theta1 = 0.0f;
                float theta2 = 0.0f;

                if (parseMessage(_rxBuffer, theta1, theta2)) {
                    _theta1 = theta1;
                    _theta2 = theta2;
                    _newCommand = true;

                    Serial.print("[BT] Comando recebido -> theta1: ");
                    Serial.print(_theta1);
                    Serial.print(" | theta2: ");
                    Serial.println(_theta2);

                    _serialBT.println("OK");
                } else {
                    Serial.print("[BT] Mensagem inválida: ");
                    Serial.println(_rxBuffer);

                    _serialBT.println("ERRO");
                }
            }

            _rxBuffer = "";
        } else {
            _rxBuffer += c;

            if (_rxBuffer.length() > 64) {
                _rxBuffer = "";
                Serial.println("[BT] Buffer excedeu limite. Limpando.");
                _serialBT.println("ERRO_BUFFER");
            }
        }
    }
}

bool BtClient::isConnected() {
    if (!_started) {
        return false;
    }

    return _serialBT.hasClient();
}

bool BtClient::hasNewCommand() const {
    return _newCommand;
}

void BtClient::clearNewCommandFlag() {
    _newCommand = false;
}

float BtClient::getTheta1() const {
    return _theta1;
}

float BtClient::getTheta2() const {
    return _theta2;
}

bool BtClient::parseMessage(const String& message, float& theta1, float& theta2) {
    int commaIndex = message.indexOf(',');

    if (commaIndex < 0) {
        return false;
    }

    String theta1Str = message.substring(0, commaIndex);
    String theta2Str = message.substring(commaIndex + 1);

    theta1Str.trim();
    theta2Str.trim();

    if (theta1Str.length() == 0 || theta2Str.length() == 0) {
        return false;
    }

    char* endPtr1 = nullptr;
    char* endPtr2 = nullptr;

    theta1 = strtof(theta1Str.c_str(), &endPtr1);
    theta2 = strtof(theta2Str.c_str(), &endPtr2);

    if (*endPtr1 != '\0' || *endPtr2 != '\0') {
        return false;
    }

    return true;
}