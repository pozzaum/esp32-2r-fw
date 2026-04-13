#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <Stepper.h>

class Motor
{
private:
    const uint8_t pin1, pin2, pin3, pin4;
    const int16_t lower_limit, upper_limit, steps_per_rev;
    int step_counter;
    Stepper motor;


public:
    Motor(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, int16_t lower_limit, int16_t upper_limit, uint16_t stepsPerRevolution);

    void set_speed(uint16_t rpm);
    void step_movement(int steps);
    void angle_movement(float angle);
    void reset_position();

    ~Motor();
};

#endif