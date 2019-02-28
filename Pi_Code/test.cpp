#include <stdio.h>
#include <wiringPi.h>
int mix_dir = 2;
int mix_step = 3;

void setup()
{
	printf("Settping up Pi for Smart Bar...\n");
	printf("Initialize wiringPi...\n");
	wiringPiSetup();

	printf("Setting pin declarations...\n");
	printf("Mix Pump Direction Pin: %d\n", mix_dir);
	printf("Mix Pump Step Pin: %d\n", mix_step);

	pinMode(mix_dir, OUTPUT);
	pinMode(mix_step, OUTPUT);

	digitalWrite(mix_dir, LOW);
	digitalWrite(mix_step, LOW);
}

void run()
{
//	int i = 0;
	digitalWrite(mix_dir, HIGH);
	while(true)
	{
		digitalWrite(mix_step, HIGH);
		delayMicroseconds(75);
		digitalWrite(mix_step, LOW);
		delayMicroseconds(75);
	}
}

int main(void)
{
	setup();
	run();
}
