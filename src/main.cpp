#include <AccelStepper.h>
#include "defines.h"

// Configuração: usamos HALF4WIRE (8) para o 28BYJ-48 ficar mais suave
// A ordem dos pinos DEVE SER: IN1, IN3, IN2, IN4
AccelStepper shoulder(AccelStepper::HALF4WIRE, SHOULDER_PIN1, SHOULDER_PIN3, SHOULDER_PIN2, SHOULDER_PIN4);
AccelStepper elbow(AccelStepper::HALF4WIRE, ELBOW_PIN1, ELBOW_PIN3, ELBOW_PIN2, ELBOW_PIN4);

void setup() {
  Serial.begin(115200);
  Serial.println("Send two target positions separated by space (e.g. '1000 -500'):");

  // Configurações do Motor 1
  shoulder.setMaxSpeed(1000.0);      // Velocidade máxima (passos por segundo)
  shoulder.setAcceleration(500.0);   // Aceleração
  
  // Configurações do Motor 2
  elbow.setMaxSpeed(1000.0);
  elbow.setAcceleration(500.0);
}

void loop() {
  // ESTES COMANDOS NÃO PODEM TER DELAY NO LOOP
  // Eles precisam rodar "livres" para o motor girar macio
  shoulder.run();
  elbow.run();

  //Exemplo: Quando o motor 1 terminar, mande ele voltar
  if (Serial.available() > 0) {
    long targetShoulder = Serial.parseInt();
    long targetElbow = Serial.parseInt();

    // Consume the rest of the line from the buffer
    while (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') break;
    }

    shoulder.moveTo(targetShoulder);
    elbow.moveTo(targetElbow);
    
    Serial.print("Moving shoulder to: ");
    Serial.print(targetShoulder);
    Serial.print(" | elbow to: ");
    Serial.println(targetElbow);
  }
}