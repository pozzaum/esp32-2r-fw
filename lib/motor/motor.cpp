 #include "motor.h"
 
Motor::Motor(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4,
             int16_t lower_limit, int16_t upper_limit,
             uint16_t steps_per_rev
             )
    : pin1(p1),
      pin2(p2),
      pin3(p3),
      pin4(p4),
      lower_limit(lower_limit),
      upper_limit(upper_limit),
      steps_per_rev(steps_per_rev),
      motor(steps_per_rev, pin1, pin3, pin2, pin4)   // ← AQUI é o correto
{
}


void Motor::set_speed(uint16_t rpm){
    motor.setSpeed(rpm);
}

void Motor::step_movement(int steps){
    step_counter += steps;
    motor.step(steps);
}

void Motor::angle_movement(float angle){
    int steps = steps_per_rev * angle / 360;
    step_movement(steps);
}

void Motor::reset_position(){
    step_movement(-step_counter);
}



Motor::~Motor(){}