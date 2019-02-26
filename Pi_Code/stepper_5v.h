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
        void setup();
        void step(std::vector<bool> sequence);
    public:
        Stepper_5v(std::string name, int a1, int a2, int a3, int a4);
        void move(int direction);
}