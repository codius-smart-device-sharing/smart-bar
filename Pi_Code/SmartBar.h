#pragma once

#include "Pinout.h"
#include "Stepper.h"
#include "Stepper_5v.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <mutex>

#include <wiringPi.h>

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
            static std::map<std::string, int> quantities;
            static void activate_pump(int pump_num);
            static void eject_cup();
            static void make_drink(std::map<std::string, int> recipe);
            static void init_bar();

        private:
            std::map<std::string, int> motors;
            Stepper_5v eject;
    };

    class Delivery
    {
        public:
            static void move_motor(std::string motor, std::string dir);
            static void home();
            static void deliver(/*destination*/);
            static void init_delivery();

        private:
            Stepper x;
            Stepper y;
            Stepper_5v clamp;
            Stepper_5v rotate;
            bool clamp_open;
    };

    static void initialize();
}