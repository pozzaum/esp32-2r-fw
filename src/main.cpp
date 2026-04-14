#include "main.h"

// A ordem dos pinos DEVE SER: IN1, IN3, IN2, IN4
AccelStepper shoulder(
    AccelStepper::HALF4WIRE,
    SHOULDER_PIN1, SHOULDER_PIN3, SHOULDER_PIN2, SHOULDER_PIN4
);

AccelStepper elbow(
    AccelStepper::HALF4WIRE,
    ELBOW_PIN1, ELBOW_PIN3, ELBOW_PIN2, ELBOW_PIN4
);

SerialClient serialClient;

void setup() {
    serialClient.begin(115200);

    shoulder.setMaxSpeed(1000.0);
    shoulder.setAcceleration(500.0);

    elbow.setMaxSpeed(1000.0);
    elbow.setAcceleration(500.0);
}

void loop() {
    // não colocar delay aqui
    shoulder.run();
    elbow.run();

    serialClient.update();

    if (serialClient.hasNewCommand()) {
        long targetShoulder = serialClient.getTargetShoulder();
        long targetElbow = serialClient.getTargetElbow();

        shoulder.moveTo(targetShoulder);
        elbow.moveTo(targetElbow);

        Serial.print("Moving shoulder to: ");
        Serial.print(targetShoulder);
        Serial.print(" | elbow to: ");
        Serial.println(targetElbow);

        serialClient.clearNewCommandFlag();
    }
}