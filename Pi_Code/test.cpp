#include "SmartBar.h"

using namespace SmartBar;

int main(int argc, char* argv[])
{

	// Initialize WiringPi
	wiringPiSetup();

	// Initialize SmartBar
	initialize();

	// Test Everything
	std::cout << "----- Testing System -----" << std::endl;
	std::cout << "--- Testing Switches ---" << std::endl;
	/* Switches */
	bool switch_test = true;
	while (switch_test)
	{
		Switch::read_switch(0);
		Switch::read_switch(1);
		Switch::read_switch(2);
		Switch::read_switch(3);
		if (Switch::x_isClicked && Switch::y_isClicked)
		{
			switch_test = false;
		}
		else
		{
			if (Switch::x_isClicked)
			{
				std::cout << "X Clicked" << std::endl;
			}
			if (Switch::y_isClicked)
			{
				std::cout << "Y Clicked" << std::endl;
			}

			if (Switch::rot_isClicked)
			{
				std::cout << "Rotation Clicked" << std::endl;
			}

			if (Switch::clamp_isClicked)
			{
				std::cout << "Clamp Clicked" << std::endl;
			}
		}
	}
	std::cout << "--- Switches Done ---\n" << std::endl;

	std::cout << "--- Testing Bar ---" << std::endl;
	/* Bar */
	std::cout << "--- Testing Pumps ---" << std::endl;
	/* Run Pumps */
	bool pump_test = true;
	while (pump_test)
	{
		Switch::read_switch(0);
		if (Switch::x_isClicked)
		{
			pump_test = false;
		}
		else
		{
			// Pump 1
			Switch::read_switch(3);
			while (!Switch::clamp_isClicked)
			{
				Switch::read_switch(3);
				activate_pump(0);
			}

			delay(500);
			// Pump 2
			Switch::read_switch(3);
			while (!Switch::clamp_isClicked)
			{
				Switch::read_switch(3);
				activate_pump(1);
			}

			delay(500);
			// Pump 3
			Switch::read_switch(3);
			while (!Switch::clamp_isClicked)
			{
				Switch::read_switch(3);
				activate_pump(2);
			}

			delay(500);
			// Pump 4
			Switch::read_switch(3);
			while (!Switch::clamp_isClicked)
			{
				Switch::read_switch(3);
				activate_pump(3);
			}

			delay(500);
			// Pump 5
			Switch::read_switch(3);
			while (!Switch::clamp_isClicked)
			{
				Switch::read_switch(3);
				activate_pump(4);
			}

			delay(500);
			// Pump 6
			Switch::read_switch(3);
			while (!Switch::clamp_isClicked)
			{
				Switch::read_switch(3);
				activate_pump(5);
			}
		}
	}
	std::cout << "--- Done ---" << std::endl;
	std::cout << "--- Testing Cup Ejection ---" << std::endl;
	/* Test Cup Ejection */
	bool eject_test = true;
	while (eject_test)
	{
		Switch::read_switch(0);
		if (Switch::x_isClicked)
		{
			eject_test = false;
		}
		else
		{
			Switch::read_switch(3);
			if (Switch::clamp_isClicked)
			{
				Bar::eject_cup();
			}
		}
	}
	std::cout << "--- Done ---" << std::endl;
	std::cout << "--- Testing Make Drink ---" << std::endl;
	/* Make a drink */
	std::map<std::string, int> recipe;
	recipe.insert(std::pair<std::string, int>("Rum", 1));
	recipe.insert(std::pair<std::string, int>("Coke", 1));
	bool drink_test = true;
	while (drink_test)
	{
		Switch::read_switch(0);
		if (Switch::x_isClicked)
		{
			drink_test = false;
		}
		else
		{
			Switch::read_switch(3);
			if (Switch::clamp_isClicked)
			{
				Bar::make_drink(recipe);
			}
		}	
	}
	std::cout << "--- Done ---" << std::endl;
	std::cout << "--- Bar Done ---\n" << std::endl;

	std::cout << "--- Testing Delivery ---" << std::endl;
	/* Delivery */
	std::cout << "--- Testing Motors ---" << std::endl;
	/* Move Motors */
	int click_count = 0;
	while (true)
	{
		Switch::read_switch(3);
		if (Switch::clamp_isClicked && click_count == 0)
		{
			Delivery::move_motor("X", "OUT");
			click_count++;
		}
		else if (Switch::clamp_isClicked && click_count == 1)
		{
			Delivery::move_motor("Y", "UP");
			click_count++;
		}
		else if (Switch::clamp_isClicked && click_count == 2)
		{
			Delivery::move_motor("Rotate", "OUT");
			click_count++;
		}
		else if (Switch::clamp_isClicked && click_count == 3)
		{
			Delivery::move_motor("Clamp", "OUT");
			click_count++;
		}
		else if (click_count == 4)
		{
			break;
		}
	}
	std::cout << "--- Done ---" << std::endl;
	std::cout << "--- Testing Home ---" << std::endl;
	/* Home */
	while (true)
	{
		Switch::read_switch(3);
		if (Switch::clamp_isClicked)
		{
			break;
		}
	}
	Delivery::home();
	std::cout << "--- Done ---" << std::endl;
	std::cout << "--- Testing Deliver ---" << std::endl;
	/* Deliver */	
	while (true)
	{
		Switch::read_switch(3);
		if (Switch::clamp_isClicked)
		{
			break;
		}
	}
	Delivery::deliver();
	std::cout << "--- Done ---" << std::endl;
	std::cout << "--- Delivery Done ---\n" << std::endl;
	std::cout << "----- Testing Done -----\n" << std::endl;
}
