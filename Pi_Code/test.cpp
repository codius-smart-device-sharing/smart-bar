#include "Pinout.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Stepper.h"
#include "Stepper_5v.h"
#include <wiringPi.h>

int main(int argc, char* argv[])
{
	wiringPiSetup();

	// printf("Testing X Motor\n");
	// Stepper x ("X", DIR_X, STEP_X);
	// x.move(1, 50000);

	// printf("Testing Y Motor\n");
	// Stepper y ("Y", DIR_Y, STEP_Y);
	// y.move(1, 50000);

	// digitalWrite(DIR_X, LOW);
	// digitalWrite(STEP_X, LOW);
	// digitalWrite(DIR_Y, LOW);
	// digitalWrite(STEP_Y, LOW);

	// pinMode(GAL_CLK, OUTPUT);
	// pinMode(STEP_IN, OUTPUT);
	// pinMode(SEL2, OUTPUT);
	// pinMode(SEL1, OUTPUT);
	// pinMode(SEL0, OUTPUT);

	// int del = 95;
	// // MIX1
	// digitalWrite(SEL0, HIGH);
	// digitalWrite(SEL1, HIGH);
	// digitalWrite(SEL2, LOW);
	// // printf("Starting Delay\n");
	// // delay(10000);
    // for(int i = 0; i < 50000; i++)
    // {
    //     digitalWrite(STEP_IN, HIGH);
    //     delayMicroseconds(del);
    //     digitalWrite(STEP_IN, LOW);
    //     delayMicroseconds(del);
    // }

	// // MIX2
	// digitalWrite(SEL0, LOW);
	// digitalWrite(SEL1, LOW);
	// digitalWrite(SEL2, HIGH);
	// // printf("Starting Delay\n");
	// // delay(10000);
    // for(int i = 0; i < 50000; i++)
    // {
    //     digitalWrite(STEP_IN, HIGH);
    //     delayMicroseconds(del);
    //     digitalWrite(STEP_IN, LOW);
    //     delayMicroseconds(del);
    // }

	// // MIX3
	// digitalWrite(SEL0, HIGH);
	// digitalWrite(SEL1, LOW);
	// digitalWrite(SEL2, HIGH);
	// // printf("Starting Delay\n");
	// // delay(10000);
    // for(int i = 0; i < 50000; i++)
    // {
    //     digitalWrite(STEP_IN, HIGH);
    //     delayMicroseconds(del);
    //     digitalWrite(STEP_IN, LOW);
    //     delayMicroseconds(del);
    // }

	// // SPIRIT1
	// digitalWrite(SEL0, LOW);
	// digitalWrite(SEL1, LOW);
	// digitalWrite(SEL2, LOW);
	// // printf("Starting Delay\n");
	// // delay(10000);
    // for(int i = 0; i < 50000; i++)
    // {
    //     digitalWrite(STEP_IN, HIGH);
    //     delayMicroseconds(del);
    //     digitalWrite(STEP_IN, LOW);
    //     delayMicroseconds(del);
    // }

	// // SPIRIT2
	// digitalWrite(SEL0, HIGH);
	// digitalWrite(SEL1, LOW);
	// digitalWrite(SEL2, LOW);
	// // printf("Starting Delay\n");
	// // delay(10000);
    // for(int i = 0; i < 50000; i++)
    // {
    //     digitalWrite(STEP_IN, HIGH);
    //     delayMicroseconds(del);
    //     digitalWrite(STEP_IN, LOW);
    //     delayMicroseconds(del);
    // }

	// // SPIRIT3
	// digitalWrite(SEL0, LOW);
	// digitalWrite(SEL1, HIGH);
	// digitalWrite(SEL2, LOW);
	// // printf("Starting Delay\n");
	// // delay(10000);
    // for(int i = 0; i < 50000; i++)
    // {
    //     digitalWrite(STEP_IN, HIGH);
    //     delayMicroseconds(del);
    //     digitalWrite(STEP_IN, LOW);
    //     delayMicroseconds(del);
    // }

	// Testing Clamp 5V Motor
	std::string isOpen(argv[1]);
	Stepper_5v clamp("Clamp", CLAMP_1, CLAMP_2, CLAMP_3, CLAMP_4);
	if (isOpen == "Open")
	{
		clamp.move_5v(1, 50);
	}
	else if (isOpen == "Close")
	{
		clamp.move_5v(0, 50);
	}
}
