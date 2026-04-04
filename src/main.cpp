#include <Stepper.h>
#include <Arduino.h>

#define STEPS_PER_REV 2048  // 28BYJ-48 = 2048 passos por volta
#define REV_RPM_SPEED 15    // velocidade otima
#define SHOULDER_REDUCTION_RATION 5 

const int stepsPerRevolution = 2048;

const int shoulderPin1 = 13;
const int shoulderPin2 = 12;
const int shoulderPin3 = 14;
const int shoulderPin4 = 27;

const int elbowPin1 = 26;
const int elbowPin2 = 25;
const int elbowPin3 = 33;
const int elbowPin4 = 32; 

const int buttonPin = 34;

// Instância do motor
Stepper shoulder(stepsPerRevolution, shoulderPin1, shoulderPin3, shoulderPin2, shoulderPin4);
Stepper elbow(stepsPerRevolution, elbowPin1, elbowPin3, elbowPin2, elbowPin4);


void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  shoulder.setSpeed(REV_RPM_SPEED);  // RPM
  elbow.setSpeed(REV_RPM_SPEED);     // RPM

}

void loop() {

  shoulder.step(STEPS_PER_REV * SHOULDER_REDUCTION_RATION);
  elbow.step(STEPS_PER_REV);
  delay(5000);

}