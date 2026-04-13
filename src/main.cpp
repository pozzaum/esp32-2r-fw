#include "main.h"

// Definições globais
Motor shoulder(
    SHOULDER_PIN1,
    SHOULDER_PIN2,
    SHOULDER_PIN3,
    SHOULDER_PIN4,
    SHOULDER_LOWER_LIMIT,
    SHOULDER_UPPER_LIMIT,
    STEPS_PER_REV
);

Motor elbow(
    ELBOW_PIN1,
    ELBOW_PIN2,
    ELBOW_PIN3,
    ELBOW_PIN4,
    ELBOW_LOWER_LIMIT,
    ELBOW_UPPER_LIMIT,
    STEPS_PER_REV
);

BtClient btClient;

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(115200);

    shoulder.set_speed(REV_RPM_SPEED);
    elbow.set_speed(REV_RPM_SPEED);

    btClient.begin("ESP32_2R");

    Serial.println("Sistema iniciado.");
}

void loop() {
    btClient.update();

    if (btClient.hasNewCommand()) {
        float theta1 = btClient.getTheta1();
        float theta2 = btClient.getTheta2();

        Serial.print("Theta1 recebido: ");
        Serial.println(theta1);

        Serial.print("Theta2 recebido: ");
        Serial.println(theta2);

        // proteção física do ombro
        if (theta1 < -90.0f || theta1 > 90.0f) {
            Serial.println("Theta1 fora do limite fisico. Comando ignorado.");
            btClient.clearNewCommandFlag();
            return;
        }

        // Aqui, por enquanto, só exemplo direto:
        shoulder.reset_position();
        elbow.reset_position();

        shoulder.angle_movement(theta1 * SHOULDER_REDUCTION_RATION);
        elbow.angle_movement(theta2);

        btClient.clearNewCommandFlag();
    }
}