#include "Stepper.h"
using namespace std;

void Stepper::setup()
{
    pinMode(this->dir_pin, OUTPUT);
    pinMode(this->step_pin, OUTPUT);

    digitalWrite(this->dir_pin, LOW);
    digitalWrite(this->step_pin, LOW);
}

void Stepper::move(int direction, int rotations)
{
    if (direction)
    {
	    digitalWrite(this->dir_pin, HIGH);
    }
    else
    {
        digitalWrite(this->dir_pin, LOW);
    }

    for(int i = 0; i < rotations; i++)
    {
        digitalWrite(this->step_pin, HIGH);
        delayMicroseconds(80);
        digitalWrite(this->step_pin, LOW);
        delayMicroseconds(80);
    }
}

Stepper::Stepper(string name, int dir_pin, int step_pin)
{
    this->name = name;
    this->dir_pin = dir_pin;
    this->step_pin = step_pin;
    this->setup();
}