#include "stepper_5v.h"
using namespace std;

void Stepper_5v::setup()
{
    this->forward_sequence.push(vector<bool> {true, false, false, false});
	this->forward_sequence.push(vector<bool> {true, true, false, false});
	this->forward_sequence.push(vector<bool> {false, true, false, false});
	this->forward_sequence.push(vector<bool> {false, true, true, false});
	this->forward_sequence.push(vector<bool> {false, false, true, false});
	this->forward_sequence.push(vector<bool> {false, false, true, true});
	this->forward_sequence.push(vector<bool> {false, false, false, true});
	this->forward_sequence.push(vector<bool> {true, false, false, true});

    pinMode(this->a1, OUTPUT);
    pinMode(this->a2, OUTPUT);
    pinMode(this->a3, OUTPUT);
    pinMode(this->a4, OUTPUT);

    digitalWrite(this->a1, LOW);
    digitalWrite(this->a2, LOW);
    digitalWrite(this->a3, LOW);
    digitalWrite(this->a4, LOW);
}

void Stepper_5v::step(vector<bool> sequence)
{
    if (sequence[0])
	{
		digitalWrite(this->a1, HIGH);
	}
	else
	{
		digitalWrite(this->a1, LOW);
	}
	
	if (sequence[1])
	{
		digitalWrite(this->a2, HIGH);
	}
	else
	{
		digitalWrite(this->a2, LOW);
	}	
	
	if (sequence[2])
	{
		digitalWrite(this->a3, HIGH);
	}
	else
	{
		digitalWrite(this->a3, LOW);
	}	
	
	if (sequence[3])
	{
		digitalWrite(this->a4, HIGH);
	}
	else
	{
		digitalWrite(this->a4, LOW);
	}
}

void Stepper_5v::move(int direction)
{
	vector<bool> sequence;
    if (direction)
    {
        for (int i = 0; i < rotations; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                sequence = this->forward_sequence.front();
                this->forward_sequence.pop();
                this->forward_sequence.push(sequence);
                this->step(sequence);
                delay(1);
            }
        }
    }

	digitalWrite(this->a1, LOW);
	digitalWrite(this->a2, LOW);
	digitalWrite(this->a3, LOW);
	digitalWrite(this->a4, LOW);
}

Stepper_5v::Stepper_5v(string name, int a1, int a2, int a3, int a4)
{
    this->name = name;
    this->a1 = a1;
    this->a2 = a2;
    this->a3 = a3;
    this->a4 = a4;
    this->setup();
}