#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "wiringPi.h"
#include <queue>
#include <vector>
#include <string>

struct stepper {
    std::string name;
    int dir;
    int step;
};

struct stepper_5v {
    std::string name;
    int a1;
    int a2;
    int a3;
    int a4;
};