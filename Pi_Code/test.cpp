#include "Pinout.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Stepper.h"
#include "Stepper_5v.h"
#include <wiringPi.h>

bool isOpen = true;
/* Motor Declarations */
Stepper_5v clamp("Clamp", CLAMP_1, CLAMP_2, CLAMP_3, CLAMP_4);
Stepper_5v eject("Ejector", EJECT_1, EJECT_2, EJECT_3, EJECT_4);
Stepper x("X", DIR_X, STEP_X);
Stepper y("Y", DIR_Y, STEP_Y);
/* Rotation Motor */

void eject_cup()
{
	eject.move(1, 50);
}

void move_clamp(std::string action)
{
	if (action == "Open" && !isOpen)
	{
		clamp.move_5v(1, 50);
		isOpen = true;
	}
	else if (action == "Close" && isOpen)
	{
		clamp.move_5v(0, 50);
		isOpen = false;
	}
}

void activate_pump(int pump_num/*, int amount*/)
{
	int del = 95;
	switch (pump_num)
	{
		case 0: // 000 Spirit1
			digitalWrite(SEL2, LOW);
			digitalWrite(SEL1, LOW);
			digitalWrite(SEL0, LOW);
			break;

		case 1: // 001 Spirit2
			digitalWrite(SEL2, LOW);
			digitalWrite(SEL1, LOW);
			digitalWrite(SEL0, HIGH);
			break;

		case 2: // 010 Spirit3
			digitalWrite(SEL2, LOW);
			digitalWrite(SEL1, HIGH);
			digitalWrite(SEL0, LOW);
			break;

		case 3: // 011 Mix1
			digitalWrite(SEL2, LOW);
			digitalWrite(SEL1, HIGH);
			digitalWrite(SEL0, HIGH);
			break;

		case 4: // 100 Mix2
			digitalWrite(SEL2, HIGH);
			digitalWrite(SEL1, LOW);
			digitalWrite(SEL0, LOW);
			break;

		case 5: // 101 Mix3
			digitalWrite(SEL2, HIGH);
			digitalWrite(SEL1, LOW);
			digitalWrite(SEL0, HIGH);
			break;
	
		default:
			break;
	}

    for(int i = 0; i < 50000; i++)
    {
        digitalWrite(STEP_IN, HIGH);
        delayMicroseconds(del);
        digitalWrite(STEP_IN, LOW);
        delayMicroseconds(del);
    }

	digitalWrite(STEP_IN, LOW);
	digitalWrite(SEL2, LOW);
	digitalWrite(SEL1, LOW);
	digitalWrite(SEL0, LOW);
}

void make_drink()
{
	eject_cup();
	delay(500);
	activate_pump(0);
	activate_pump(3)
}

void home()
{
	// rotate in
	while (digitalRead(ROT_STOP))
	{
		// rotate in
	}
	// close clamp
	// move_clamp("Close");
	// move y to endstop
	while (digitalRead(Y_STOP))
	{
		y.move(1, 50);
	}
	// open clamp
	move_clamp("Open");
	// move x to endstop
	while (digitalRead(X_STOP))
	{
		x.move(1, 50);
	}
}

void deliver(auto address)
{
	// home
	home();
	// close clamp
	move_clamp("Close");
	// raise y
	y.move(0, 25000);
	// move x to position
	x.move(1, 25000);
	// rotate out
	// lower y
	y.move(1. 25000);
	// open clamp
	move_clamp("Open");
	// raise y
	y.move(0, 25000);
	// home again
	home();
}

int main(int argc, char* argv[])
{
	// Initialize WiringPi
	wiringPiSetup();

	// Set pump pins
	pinMode(STEP_IN, OUTPUT);
	pinMode(SEL2, OUTPUT);
	pinMode(SEL1, OUTPUT);
	pinMode(SEL0, OUTPUT);

	// Set endstop pins
	pinMode(X_STOP, INPUT);
	pinMode(Y_STOP, INPUT);
	pinMode(ROT_STOP, INPUT);
	pinMode(CLAMP_STOP, INPUT);
	pullUpDnControl(X_STOP, PUD_UP);
	pullUpDnControl(Y_STOP, PUD_UP);
	pullUpDnControl(ROT_STOP, PUD_UP);
	pullUpDnControl(CLAMP_STOP, PUD_UP);

	make_drink();
	deliver();
}
