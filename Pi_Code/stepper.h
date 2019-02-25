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