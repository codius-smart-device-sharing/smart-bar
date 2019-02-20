#include <stdio.h>
#include <wiringPi.h>
#include "mix_pumps.h"

int main(void)
{
	printf("Settping up Pi for Smart Bar...\n");
	printf("Initialize wiringPi...\n");
	wiringPiSetup();

	printf("Setting pin declarations...\n");
	printf("Direction Pin: %d\n", dir);
	printf("Step Pin: %d\n", step);

	pinMode(dir, OUTPUT);
	pinMode(step, OUTPUT);
}
