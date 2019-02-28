#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "wiringPi.h"
#include <queue>
#include <vector>
#include <string>

class Stepper {
    private:
        std::string name;
        int dir_pin;
        int step_pin;
        void setup();
    public:
        Stepper(std::string name, int dir_pin, int step_pin);
        void move(int direction, int rotations);
};