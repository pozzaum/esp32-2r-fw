#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <stdint.h>

#include "defines.h"
#include "motor.h"
#include "bt_client.h"

// Declarações globais
extern Motor shoulder;
extern Motor elbow;
extern BtClient btClient;

#endif