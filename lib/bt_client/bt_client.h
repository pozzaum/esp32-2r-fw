#ifndef BT_CLIENT_H
#define BT_CLIENT_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class BtClient {
public:
    BtClient();

    bool begin(const String& device_name);
    void update();

    bool isConnected();
    bool hasNewCommand() const;
    void clearNewCommandFlag();

    float getTheta1() const;
    float getTheta2() const;

private:
    BluetoothSerial _serialBT;

    String _rxBuffer;
    float _theta1;
    float _theta2;
    bool _newCommand;
    bool _started;

    bool parseMessage(const String& message, float& theta1, float& theta2);
};

#endif