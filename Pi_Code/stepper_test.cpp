#include "Stepper.h"
#include "Stepper_5v.h"
using namespace std;

// stepper pump;
// stepper x;
// stepper y;
// stepper rotation;
// stepper_5v clamp;
// stepper_5v eject;
int prime = 8;
int dispense = 9;
int open_close = 7;
bool isDispense = true;
bool isOpen = false;

int main() 
{
	// Init wiringPi
	wiringPiSetup();
	pinMode(prime, INPUT);
	pinMode(dispense, INPUT);
	pinMode(open_close, INPUT);
	pullUpDnControl (prime, PUD_UP) ;
	pullUpDnControl (dispense, PUD_UP) ;
	pullUpDnControl (open_close, PUD_UP) ;

	// Init steppers
	Stepper_5v clamp ("Clamp", 22, 23, 24, 25);
	Stepper pump ("Pump", 0, 2);

	// Open Clamp
//	clamp.setPins_5v();
	delay(10);
	clamp.move_5v(0, 50);

	// Run
	while (true)
	{
		while (digitalRead(prime) == 0)
		{
			pump.move(1, 1600);
		}

		if (digitalRead(dispense) == 0)
		{
			if (isDispense)
			{
				pump.move(1, 1600);
				isDispense = false;
			}
			else if (!isDispense)
			{
				isDispense = true;
			}
		}
		

		if (digitalRead(open_close) == 0)
		{
			if (isOpen)
			{
				clamp.move_5v(1, 50);
				isOpen = false;
			}
			else if (!isOpen)
			{
				clamp.move_5v(0, 50);
				isOpen = true;
			}
		}
	}

	return 0;
}