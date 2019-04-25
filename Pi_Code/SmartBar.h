#pragma once
#include "wiringPi.h"
#include "Stepper.h"
#include "Stepper_5v.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <mutex>

namespace SmartBar
{
    class Switch
    {
        public:
            static bool x_isClicked;
            static bool x_wasClicked;
            static bool y_isClicked;
            static bool y_wasClicked;
            static bool rot_isClicked;
            static bool rot_wasClicked;
            static bool clamp_isClicked;
            static bool clamp_wasClicked;

            static void read_switch(int sw);
            static void init_switches();
    };

    class Bar
    {
        public:
            static std::mutex m;
            static int cup_count;
            static void activate_pump(int pump_num, int amount);
            static void eject_cup();
            static void make_drink(std::map<std::string, int> recipe);
            static void init_bar();
            static std::map<std::string, int> quantities;
            static std::map<std::string, int> motors;
            static Stepper_5v eject;
    };

    class Delivery
    {
        public:
            static void move_motor(std::string motor, std::string dir, int destination);
            static void home();
            static void deliver(int destination);

        private:
            static Stepper x;
            static Stepper y;
            static Stepper_5v clamp;
            static Stepper_5v rotate;
            static bool clamp_open;
    };
}