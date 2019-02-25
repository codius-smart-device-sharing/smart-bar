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
        queue<vector<bool> > forward_sequence;
        queue<vector<bool> > backward_sequence;
    public:
        Stepper_5v(const std::string name, const int a1, const int a2, const int a3, const int a4);
        step(Stepper_5v& stepper, std::vector<bool> sequence);
        move(Stepper_5v& stepper, const int direction);
}