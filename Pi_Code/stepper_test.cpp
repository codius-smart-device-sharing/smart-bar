#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <vector>
#include <queue>
using namespace std;

int a1 = 25;
int a2 = 24;
int a3 = 23;
int a4 = 22;

void step(vector<bool> sequence)
{
	if (sequence[0])
	{
		digitalWrite(a1, HIGH);
	}
	else
	{
		digitalWrite(a1, LOW);
	}
	
	if (sequence[1])
	{
		digitalWrite(a2, HIGH);
	}
	else
	{
		digitalWrite(a2, LOW);
	}	
	
	if (sequence[2])
	{
		digitalWrite(a3, HIGH);
	}
	else
	{
		digitalWrite(a3, LOW);
	}	
	
	if (sequence[3])
	{
		digitalWrite(a4, HIGH);
	}
	else
	{
		digitalWrite(a4, LOW);
	}
}

void forward(queue<vector<bool> > sequences, int rotations)
{
	vector<bool> sequence;
	for (int i = 0; i < rotations; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			sequence = sequences.front();
			sequences.pop();
			sequences.push(sequence);
			step(sequence);
			delay(1);
		}
	}
}

int main() 
{
	wiringPiSetup();
	queue<vector<bool> > sequences;
	
	sequences.push(vector<bool> {true, false, false, false});
	sequences.push(vector<bool> {true, true, false, false});
	sequences.push(vector<bool> {false, true, false, false});
	sequences.push(vector<bool> {false, true, true, false});
	sequences.push(vector<bool> {false, false, true, false});
	sequences.push(vector<bool> {false, false, true, true});
	sequences.push(vector<bool> {false, false, false, true});
	sequences.push(vector<bool> {true, false, false, true});

	pinMode(a1, OUTPUT);
	pinMode(a2, OUTPUT);
	pinMode(a3, OUTPUT);
	pinMode(a4, OUTPUT);

	forward(sequences, 100);

	return 0;
}