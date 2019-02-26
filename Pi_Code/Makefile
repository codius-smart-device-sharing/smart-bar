stepper: stepper_test.cpp stepper_5v.cpp
	g++ -g -Wall -Werror -std=c++11 stepper_test.cpp stepper_5v.cpp -o out/stepper_test.o -lwiringPi
	sudo ./out/stepper_test.o

test: test.cpp
	g++ -g -Wall -Werror -std=c++11 test.cpp -o out/test.o -lwiringPi
	sudo ./out/test.o
