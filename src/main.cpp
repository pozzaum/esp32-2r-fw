#include "includes.h"

// instancia dos motores
Motor shoulder(SHOULDER_PIN1, SHOULDER_PIN2, SHOULDER_PIN3, SHOULDER_PIN4, SHOULDER_LOWER_LIMIT, SHOULDER_UPPER_LIMIT, STEPS_PER_REV);
Motor elbow(ELBOW_PIN1, ELBOW_PIN2, ELBOW_PIN3, ELBOW_PIN4, ELBOW_LOWER_LIMIT, ELBOW_UPPER_LIMIT, STEPS_PER_REV);


void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  shoulder.set_speed(REV_RPM_SPEED);  // RPM
  elbow.set_speed(REV_RPM_SPEED);     // RPM

}

void loop() {

  shoulder.step_movement(STEPS_PER_REV * SHOULDER_REDUCTION_RATION);
  elbow.step_movement(STEPS_PER_REV);
  delay(5000);

}