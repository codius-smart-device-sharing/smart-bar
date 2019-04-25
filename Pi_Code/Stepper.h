#pragma once

#include "wiringPi.h"
#include <string>

class Stepper {
    private:
        std::string name;
        int dir_pin;
        int step_pin;
        void setup();
    public:
        Stepper(std::string name, int dir_pin, int step_pin);
        void move(int direction, int rotations, int delay);
};