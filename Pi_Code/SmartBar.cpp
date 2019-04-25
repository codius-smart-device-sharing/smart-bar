#include "SmartBar.h"

namespace SmartBar
{
    bool Switch::x_isClicked = false;
    bool Switch::x_wasClicked = false;
    bool Switch::y_isClicked = false;
    bool Switch::y_wasClicked = false;
    bool Switch::rot_isClicked = false;
    bool Switch::rot_wasClicked = false;
    bool Switch::clamp_isClicked = false;
    bool Switch::clamp_wasClicked = false;
    int Bar::cup_count = 12;
    bool Delivery::clamp_open = false;

    // direcion and step pins from Pi to A4988
    int DIR_X = 6;
    int STEP_X = 5;
    int DIR_Y = 4;
    int STEP_Y = 1;

    // These choose the correct pump through the GAL shift register
    // Connects to GAL IN1 pin to send step signal through to A4988
                        //         _____
    int GAL_CLK = 2;    // CLK/IN |     | VCC
    int STEP_IN = 0;    // IN1    |     | I/O10 to MIX3/mot5
    int SEL2 = 7;       // IN2    |     | I/O9  to MIX2/mot4
                        // IN/PD  |     | I/O8  to MIX1/mot3
    int SEL1 = 9;       // IN3    |     | I/O7  to SPIRIT3/mot2
    int SEL0 = 8;       // IN4    |     | I/O6  to SPIRIT2/mot1
                        // IN5    |     | I/O5  to SPIRIT1/mot0
                        // IN6    |     | I/O4
                        // IN7    |     | I/O3
                        // IN8    |     | I/O2
                        // IN9    |     | I/O1
                        // GND    |_____| IN10

    // Endstop Pins to Pi (Active LOW)
    int X_STOP = 22;
    int Y_STOP = 23;
    int ROT_STOP = 24;
    int CLAMP_STOP = 25;

    // 5V Cup Ejector Pins from Pi to Motor
    int EJECT_1 = 28;
    int EJECT_2 = 29;
    int EJECT_3 = 21;
    int EJECT_4 = 14;

    // 5V Clamp Pins from Pi to Motor
    int CLAMP_1 = 10;
    int CLAMP_2 = 11;
    int CLAMP_3 = 26;
    int CLAMP_4 = 27;

    // 5V Rotation Pins from Pi to Motor
    int ROT_1 = 15;
    int ROT_2 = 16;
    int ROT_3 = 3;
    int ROT_4 = 13;

    // Init Motors
    Stepper Delivery::x("X", DIR_X, STEP_X);
    Stepper Delivery::y("Y", DIR_Y, STEP_Y);
    Stepper_5v Delivery::rotate("Rotate", ROT_1, ROT_2, ROT_3, ROT_4);
    Stepper_5v Delivery::clamp("Clamp", CLAMP_1, CLAMP_2, CLAMP_3, CLAMP_4);
    Stepper_5v Bar::eject("Ejector", EJECT_1, EJECT_2, EJECT_3, EJECT_4);

    // Init containers
    std::map<std::string, int> Bar::quantities;
    std::map<std::string, int> Bar::motors;
    std::map<int, int> destinations;

    // Init mutex
    std::mutex Bar::m;

    void Switch::read_switch(int sw)
    {
    	switch (sw)
	    {
		    case 0:
                if (!Switch::x_wasClicked && !digitalRead(X_STOP))
                {
                    Switch::x_isClicked = true;
                }
                else if (Switch::x_wasClicked && digitalRead(X_STOP))
                {
                    Switch::x_isClicked = false;
                }
                Switch::x_wasClicked = Switch::x_isClicked;
                break;

            case 1:
                if (!Switch::y_wasClicked && !digitalRead(Y_STOP))
                {
                    Switch::y_isClicked = true;
                }
                else if (Switch::y_wasClicked && digitalRead(Y_STOP))
                {
                    Switch::y_isClicked = false;
                }
                Switch::y_wasClicked = Switch::y_isClicked;
                break;
        
            case 2:
                if (!Switch::rot_wasClicked && !digitalRead(ROT_STOP))
                {
                    Switch::rot_isClicked = true;
                }
                else if (Switch::rot_wasClicked && digitalRead(ROT_STOP))
                {
                    Switch::rot_isClicked = false;
                }
                Switch::rot_wasClicked = Switch::rot_isClicked;
                break;

            case 3:
                if (!Switch::clamp_wasClicked && !digitalRead(CLAMP_STOP))
                {
                    Switch::clamp_isClicked = true;
                }
                else if (Switch::clamp_wasClicked && digitalRead(CLAMP_STOP))
                {
                    Switch::clamp_isClicked = false;
                }
                Switch::clamp_wasClicked = Switch::clamp_isClicked;
                break;

            default:
                break;
	    }   
    }

    void Switch::init_switches()
    {
        // Set endstop pins
        pinMode(X_STOP, INPUT);
        pinMode(Y_STOP, INPUT);
        pinMode(ROT_STOP, INPUT);
        pinMode(CLAMP_STOP, INPUT);

        // Set active low
        pullUpDnControl(X_STOP, PUD_UP);
        pullUpDnControl(Y_STOP, PUD_UP);
        pullUpDnControl(ROT_STOP, PUD_UP);
        pullUpDnControl(CLAMP_STOP, PUD_UP);
    }

    void Bar::activate_pump(int pump_num, int amount)
    {
    	int del = 99;
    	std::cout << "Activating pump: " << pump_num << std::endl;
    	switch (pump_num)
    	{
    		case 0: // 000 Spirit1
    			digitalWrite(SEL2, LOW);
    			digitalWrite(SEL1, LOW);
    			digitalWrite(SEL0, LOW);
    			break;

    		case 1: // 001 Spirit2
    			digitalWrite(SEL2, LOW);
    			digitalWrite(SEL1, LOW);
    			digitalWrite(SEL0, HIGH);
    			break;

    		case 2: // 010 Spirit3
    			digitalWrite(SEL2, LOW);
    			digitalWrite(SEL1, HIGH);
    			digitalWrite(SEL0, LOW);
    			break;

    		case 3: // 011 Mix1
    			digitalWrite(SEL2, LOW);
    			digitalWrite(SEL1, HIGH);
    			digitalWrite(SEL0, HIGH);
    			break;

    		case 4: // 100 Mix2
    			digitalWrite(SEL2, HIGH);
    			digitalWrite(SEL1, LOW);
    			digitalWrite(SEL0, LOW);
    			break;

    		case 5: // 101 Mix3
    			digitalWrite(SEL2, HIGH);
    			digitalWrite(SEL1, LOW);
    			digitalWrite(SEL0, HIGH);
    			break;
        
    		default:
    			break;
    	}

        for(int i = 0; i < 90000 * amount; i++)
    	// Switch::read_switch(3);
    	// while (!clamp_isClicked)
        {
    		// read_switch(3);
            digitalWrite(STEP_IN, HIGH);
            delayMicroseconds(del);
            digitalWrite(STEP_IN, LOW);
            delayMicroseconds(del);
        }

    	digitalWrite(STEP_IN, LOW);
    	digitalWrite(SEL2, LOW);
    	digitalWrite(SEL1, LOW);
    	digitalWrite(SEL0, LOW);
    }

    void Bar::eject_cup()
    {
        Bar::m.lock();
        Bar::cup_count--;
        Bar::m.unlock();

        std::cout << "Ejecting Cup" << std::endl;
    	eject.move_5v(1, 30);
    }

    void Bar::make_drink(std::map<std::string, int> recipe)
    {
        // Eject a cup
    	Bar::eject_cup();
        delay(2000);
        Delivery::move_motor("X", "OUT", 0);
        delay(1000);

        // For each item in recipe, pour designated amount
        Bar::m.lock();
        for (auto& key : recipe)
        {
            Bar::quantities[key.first] -= key.second;
        }
        Bar::m.unlock();

        for (auto& key : recipe)
        {
            Bar::activate_pump(Bar::motors[key.first], key.second);
        }
    }

    void Bar::init_bar()
    {
        // Set pump pins
        pinMode(STEP_IN, OUTPUT);
        pinMode(SEL2, OUTPUT);
        pinMode(SEL1, OUTPUT);
        pinMode(SEL0, OUTPUT);

        // Set drink amounts
        Bar::quantities.insert(std::pair<std::string, int>("Whiskey", 60));
        Bar::quantities.insert(std::pair<std::string, int>("Vodka", 60));
        Bar::quantities.insert(std::pair<std::string, int>("Rum", 60));
        Bar::quantities.insert(std::pair<std::string, int>("Coke", 33));
        Bar::quantities.insert(std::pair<std::string, int>("Sprite", 33));
        Bar::quantities.insert(std::pair<std::string, int>("Cranberry", 33));

        // Initialize item to motor dictionary
        Bar::motors.insert(std::pair<std::string, int>("Whiskey", 0));
        Bar::motors.insert(std::pair<std::string, int>("Vodka", 1));
        Bar::motors.insert(std::pair<std::string, int>("Rum", 2));
        Bar::motors.insert(std::pair<std::string, int>("Coke", 3));
        Bar::motors.insert(std::pair<std::string, int>("Sprite", 4));
        Bar::motors.insert(std::pair<std::string, int>("Cranberry", 5));

        // Initialize destinations
        destinations.insert(std::pair<int, int>(1, 3));
        destinations.insert(std::pair<int, int>(2, 12));
        destinations.insert(std::pair<int, int>(3, 9));
    }

    void Delivery::move_motor(std::string motor, std::string dir, int destination)
    {
        int dest = 0;
        if (motor == "X")
    	{
    		if (dir == "IN")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;
                Switch::read_switch(0);
    			while (!Switch::x_isClicked)
    			{
                    Switch::read_switch(0);
    				Delivery::x.move(0, 50, 90);
    			}
    		}
    		else if (dir == "OUT")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;
                /* Destination address needs to go here */
                /* Also need software endstop */
                if (destination == 0)
                {
                    dest = 1;
                }
                else
                {
                    dest = destinations[destination];
                }
                
    			Delivery::x.move(1, 2500 * dest, 90);
    		}
    	}
    	else if (motor == "Y")
    	{
    		if (dir == "UP")
    		{
                /* Need software endstop */
    			std::cout << "Moving " << motor << " " << dir << std::endl;
    			Delivery::y.move(0, 3000, 105);
    		}
    		else if (dir == "DOWN")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;

                Switch::read_switch(1);
    			while (!Switch::y_isClicked)
    			{
                    Switch::read_switch(1);
    			    Delivery::y.move(1, 250, 105);
    			}
    		}
    	}
    	else if (motor == "Rotate")
    	{
    		if (dir == "IN")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;

                Switch::read_switch(2);
                while (!Switch::rot_isClicked)
                {
                    Switch::read_switch(2);
    			    Delivery::rotate.move_5v(1, 50);
                }
    		}
    		else if (dir == "OUT")
    		{
                /* Need software endstop */
    			std::cout << "Moving " << motor << " " << dir << std::endl;
    			Delivery::rotate.move_5v(0, 500);
    		}
    	}
        else if (motor == "Clamp")
        {
            if (dir == "IN" && clamp_open)
            {
                std::cout << "Moving " << motor << " " << dir << std::endl;
                Delivery::clamp.move_5v(1, 60);
                Delivery::clamp_open = false;
            }
            else if (dir == "OUT" && !clamp_open)
            {
                std::cout << "Moving " << motor << " " << dir << std::endl;
                Delivery::clamp.move_5v(0, 40);
                Delivery::clamp_open = true;
            }
        }
    }

    void Delivery::home()
    {
        std::cout << "----- Homing System -----" << std::endl;
        //Delivery::move_motor("Rotate", "IN", 0);
        Delivery::move_motor("Y", "DOWN", 0);
        Delivery::move_motor("Clamp", "OUT", 0);
        Delivery::move_motor("X", "IN", 0);
        Delivery::move_motor("Clamp", "IN", 0);
        Delivery::move_motor("Y", "UP", 0);
        std::cout << "----- Done -----" << std::endl;
    }

    void Delivery::deliver(int destination)
    {
        std::cout << "----- Delivering Drink -----" << std::endl;
        //Delivery::home();
        //Delivery::move_motor("Clamp", "IN", destination);
        //Delivery::move_motor("Y", "UP", destination);
        Delivery::move_motor("X", "OUT", destination);
        //Delivery::move_motor("Rotate", "OUT", destination);
        Delivery::move_motor("Y", "DOWN", destination);
        //Delivery::move_motor("Clamp", "OUT", destination);
        //Delivery::move_motor("Y", "UP", destination);
    }
}


