#include "Pinout.h"
#include <stdlib.h>
#include <stdio.h>
#include "Stepper.h"
#include <wiringPi.h>

int main(int argc, char* argv[])
{
	wiringPiSetup();
	printf("Testing X Motor\n");
	Stepper x ("X", DIR_X, STEP_X);
	x.move(1, 50000);

	printf("Testing Y Motor\n");
	Stepper y ("Y", DIR_Y, STEP_Y);
	y.move(1, 50000);

}
