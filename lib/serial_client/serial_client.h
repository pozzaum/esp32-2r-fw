#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include <Arduino.h>

class SerialClient {
public:
    SerialClient();

    void begin(unsigned long baudrate);
    void update();

    bool hasNewCommand() const;
    void clearNewCommandFlag();

    long getTargetShoulder() const;
    long getTargetElbow() const;

private:
    String _rxBuffer;
    long _targetShoulder;
    long _targetElbow;
    bool _newCommand;
    bool _started;

    bool parseMessage(const String& message, long& targetShoulder, long& targetElbow);
};

#endif