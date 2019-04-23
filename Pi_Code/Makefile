stepper: stepper_test.cpp Stepper_5v.cpp Stepper.cpp
	g++ -g -Wall -Werror -std=c++11 stepper_test.cpp Stepper_5v.cpp Stepper.cpp -o out/stepper_test -lwiringPi

test: test.cpp Stepper.cpp Stepper_5v.cpp SmartBar.cpp
	g++ -g -Wall -Werror -std=c++11 Stepper.cpp Stepper_5v.cpp SmartBar.cpp test.cpp -o out/test -lwiringPi

test1: test.cpp
	g++ -g -Wall -Werror -std=c++11 test.cpp -o out/test
