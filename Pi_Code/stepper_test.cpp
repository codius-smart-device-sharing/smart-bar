#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int a1 = 26;
int a2 = 19;
int b1 = 13;
int b2 = 6;
int array[4][8] = {{true, false, false, false}, 
		   {true, true, false, false},
		   {false, true, false, false},
		   {false, true, true, false},
		   {false, false, true, false},
		   {false, false, true, true},
		   {false, false, false, true},
		   {true, false, false, true}};

void set_pins(bool array[4])
{
	if (a)
	{
		digitalWrite(a1, HIGH);
	}
	else
	{
		digitalWrite(a1, LOW);
	}	

	if (b)
	{
		digitalWrite(a2, HIGH);
	}
	else
	{
		digitalWrite(a2, LOW);
	}

	if (c)
	{
		digitalWrite(b1, HIGH);
	}
	else
	{
		digitalWrite(b1, LOW);
	}
	
	if (d)
	{
		digitalWrite(b2, HIGH);
	}
	else
	{
		digitalWrite(b2, LOW);
	}
	
int main(void)
{
	int step_count = 0;	
	for (int i = 0; i < 1000; i++)
	{
		sequence(
