#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "wiringPi.h"
#include <queue>
#include <vector>
#include <string>

class Stepper_5v 
{
    private:
        std::string name;
        int a1;
        int a2;
        int a3;
        int a4;
        std::queue<std::vector<bool> > forward_sequence;
        std::queue<std::vector<bool> > backward_sequence;
        void setup_5v();
        void step_5v(std::vector<bool> sequence);
    public:
        Stepper_5v(std::string name, int a1, int a2, int a3, int a4);
        void move_5v(int direction, int rotations);
        void setPins_5v();
};