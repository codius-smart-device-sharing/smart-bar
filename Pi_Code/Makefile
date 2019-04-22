stepper: stepper_test.cpp Stepper_5v.cpp Stepper.cpp
	g++ -g -Wall -Werror -std=c++11 stepper_test.cpp Stepper_5v.cpp Stepper.cpp -o out/stepper_test.o -lwiringPi

test: test.cpp Stepper.cpp Stepper_5v.cpp
	g++ -g -Wall -Werror -std=c++11 Stepper.cpp Stepper_5v.cpp test.cpp -o out/test.o -lwiringPi
