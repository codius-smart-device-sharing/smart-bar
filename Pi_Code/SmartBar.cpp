#include "SmartBar.h"

namespace SmartBar
{
    Switch::x_isClicked = false;
    Switch::x_wasClicked = false;
    Switch::y_isClicked = false;
    Switch::y_wasClicked = false;
    Switch::rot_isClicked = false;
    Switch::rot_wasClicked = false;
    Switch::clamp_isClicked = false;
    Switch::clamp_wasClicked = false;
    clamp_open = false;

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

    void Bar::activate_pump(int pump_num/*, int amount*/)
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

        for(int i = 0; i < 50000; i++)
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

        // For each item in recipe, pour designated amount
        Bar::m.lock();
        for (auto& key : recipe)
        {
            quantities[key.first] -= key.second;
        }
        Bar::m.unlock();
        
        for (auto& key : recipe)
        {
            activate_pump(motors[key.first]/*, key.second*/);
        }
    }

    void Bar::init_bar()
    {
        // Set cup amounts
        Bar::cup_count = 12;

        // Set drink amounts
        quantities.insert(std::pair<std::string, int>("Whiskey", 60));
        quantities.insert(std::pair<std::string, int>("Vodka", 60));
        quantities.insert(std::pair<std::string, int>("Rum", 60));
        quantities.insert(std::pair<std::string, int>("Coke", 33));
        quantities.insert(std::pair<std::string, int>("Sprite", 33));
        quantities.insert(std::pair<std::string, int>("Cranberry", 33));

        // Set pump pins
        pinMode(STEP_IN, OUTPUT);
        pinMode(SEL2, OUTPUT);
        pinMode(SEL1, OUTPUT);
        pinMode(SEL0, OUTPUT);

        // Initialize ejector motors
        Stepper_5v eject_("Ejector", EJECT_1, EJECT_2, EJECT_3, EJECT_4);
        eject = eject_;

        // Initialize item to motor dictionary
        motors.insert(std::pair<std::string, int>("Whiskey", 0));
        motors.insert(std::pair<std::string, int>("Vodka", 1));
        motors.insert(std::pair<std::string, int>("Rum", 2));
        motors.insert(std::pair<std::string, int>("Coke", 3));
        motors.insert(std::pair<std::string, int>("Sprite", 4));
        motors.insert(std::pair<std::string, int>("Cranberry", 5));
    }

    void Delivery::move_motor(std::string motor, std::string dir/*, int address*/)
    {
        if (motor == "X")
    	{
    		if (dir == "IN")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;
    			while (!Switch::x_isClicked)
    			{
                    Switch::read_switch(0);
    				x.move(0, 50);
    			}
    		}
    		else if (dir == "OUT")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;
                /* Destination address needs to go here */
                /* Also need software endstop */
    			x.move(1, 25000);
    		}
    	}
    	else if (motor == "Y")
    	{
    		if (dir == "UP")
    		{
                /* Need software endstop */
    			std::cout << "Moving " << motor << " " << dir << std::endl;
    			y.move(1, 25000);
    		}
    		else if (dir == "DOWN")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;
    			while (!Switch::y_isClicked)
    			{
                    Switch::read_switch(1);
    				y.move(0, 50);
    			}
    		}
    	}
    	else if (motor == "Rotate")
    	{
    		if (dir == "IN")
    		{
    			std::cout << "Moving " << motor << " " << dir << std::endl;
                while (!Switch::rot_isClicked)
                {
                    Switch::read_switch(2);
    			    rotate.move_5v(1, 50);
                }
    		}
    		else if (dir == "OUT")
    		{
                /* Need software endstop */
    			std::cout << "Moving " << motor << " " << dir << std::endl;
    			rotate.move_5v(0, 50);
    		}
    	}
        else if (motor == "Clamp")
        {
            if (dir == "IN" && clamp_open)
            {
                std::cout << "Moving " << motor << " " << dir << std::endl;
                clamp.move_5v(1, 50);
                clamp_open = false;
            }
            else if (dir == "OUT" && !clamp_open)
            {
                std::cout << "Moving " << motor << " " << dir << std::endl;
                clamp.move_5v(0, 50);
                clamp_open = true;
            }
        }
    }

    void Delivery::home()
    {
        std::cout << "----- Homing System -----" << std::endl;
        move_motor("Rotate", "IN");
        move_motor("Y", "DOWN");
        move_motor("Clamp", "OUT");
        move_motor("X", "IN");
        std::cout << "----- Done -----" << std::endl;
    }

    void Delivery::deliver(/* destination */)
    {
        std::cout << "----- Delivering Drink -----" << std::endl;
        Delivery::home();
        move_motor("Clamp", "IN");
        move_motor("Y", "UP");
        move_motor("X", "OUT"/*, destination*/);
        move_motor("Rotate", "OUT");
        move_motor("Y", "DOWN");
        move_motor("Clamp", "OUT");
        move_motor("Y", "UP");
        Delivery::home();
    }

    void Delivery::init_delivery()
    {
        Stepper x_("X", DIR_X, STEP_X);
        Stepper y_ ("Y", DIR_Y, STEP_Y);
        Stepper_5v clamp_("Clamp", CLAMP_1, CLAMP_2, CLAMP_3, CLAMP_4);
        Stepper_5v rotate_("Rotate", ROT_1, ROT_2, ROT_3, ROT_4);

        x = x_;
        y = y_;
        clamp = clamp_;
        rotate = rotate_;
    }

    void initialize()
    {
        Switch::init_switches();
        Bar::init_bar();
        Delivery::init_delivery();
    }
}


