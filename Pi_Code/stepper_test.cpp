#include "stepper.h"
#include "stepper_5v.h"
using namespace std;

// stepper pump;
// stepper x;
// stepper y;
// stepper rotation;
stepper_5v clamp;
// stepper_5v eject;
void step_5v(vector<bool> sequence, stepper_5v stepper);
void forward_5v(queue<vector<bool> > sequences, int rotations, stepper_5v stepper);
void setup();

void setup()
{
	// Init wiringPi
	wiringPiSetup();

	// Init 5V stepper coil sequence
	sequences.push(vector<bool> {true, false, false, false});
	sequences.push(vector<bool> {true, true, false, false});
	sequences.push(vector<bool> {false, true, false, false});
	sequences.push(vector<bool> {false, true, true, false});
	sequences.push(vector<bool> {false, false, true, false});
	sequences.push(vector<bool> {false, false, true, true});
	sequences.push(vector<bool> {false, false, false, true});
	sequences.push(vector<bool> {true, false, false, true});

	// Init Clamp Motor Pins
	clamp.name = "Clamp Motor";
	clamp.a1 = 25;
	clamp.a2 = 24;
	clamp.a3 = 23;
	clamp.a4 = 22;
	pinMode(clamp.a1, OUTPUT);
	pinMode(clamp.a2, OUTPUT);
	pinMode(clamp.a3, OUTPUT);
	pinMode(clamp.a4, OUTPUT);
	
	// Init Ejector Motor Pins
	// eject.name = "Ejector Motor";
	// eject.a1 = ;
	// eject.a2 = ;
	// eject.a3 = ;
	// eject.a4 = ;
	// pinMode(eject.a1, OUTPUT);
	// pinMode(eject.a2, OUTPUT);
	// pinMode(eject.a3, OUTPUT);
	// pinMode(eject.a4, OUTPUT);

	// Init Pump Motor Pins
	// pump.name = "Pump Motor";
	// pump.dir = ;
	// pump.step = ;
	// pinMode(pump.dir, OUTPUT);
	// pinMode(pump.step, OUTPUT);

	// Init X Axis Motor Pins
	// x.name = "X Motor";
	// x.dir = ;
	// x.step = ;
	// pinMode(x.dir, OUTPUT);
	// pinMode(x.step, OUTPUT);

	// Init Y Axis Motor Pins
	// y.name = "Y Motor";
	// y.dir = ;
	// y.step = ;
	// pinMode(y.dir, OUTPUT);
	// pinMode(y.step, OUTPUT);

	// Init Rotation Axis Motor Pins
	// rotation.name = "Rotation Motor";
	// rotation.dir = ;
	// rotation.step = ;
	// pinMode(rotation.dir, OUTPUT);
	// pinMode(rotation.step, OUTPUT);
}

void step_5v(vector<bool> sequence, stepper_5v stepper)
{
	if (sequence[0])
	{
		digitalWrite(stepper.a1, HIGH);
	}
	else
	{
		digitalWrite(stepper.a1, LOW);
	}
	
	if (sequence[1])
	{
		digitalWrite(stepper.a2, HIGH);
	}
	else
	{
		digitalWrite(stepper.a2, LOW);
	}	
	
	if (sequence[2])
	{
		digitalWrite(stepper.a3, HIGH);
	}
	else
	{
		digitalWrite(stepper.a3, LOW);
	}	
	
	if (sequence[3])
	{
		digitalWrite(stepper.a4, HIGH);
	}
	else
	{
		digitalWrite(stepper.a4, LOW);
	}
}

void forward_5v(queue<vector<bool> > sequences, int rotations, stepper_5v stepper)
{
	vector<bool> sequence;
	for (int i = 0; i < rotations; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sequence = sequences.front();
			sequences.pop();
			sequences.push(sequence);
			step_5v(sequence, stepper);
			delay(1);
		}
	}

	digitalWrite(stepper.a1, LOW);
	digitalWrite(stepper.a2, LOW);
	digitalWrite(stepper.a3, LOW);
	digitalWrite(stepper.a4, LOW);
}

int main() 
{
	setup();
	forward_5v(sequences, 10000, clamp);

	return 0;
}