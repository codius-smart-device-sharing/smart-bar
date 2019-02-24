hello: test.cpp
	g++ -g test.cpp -o out/test.o -lwiringPi
	g++ -g -Wall -Werror -std=c++11 stepper_test.cpp -o out/stepper_test.o -lwiringPi

test:
	# sudo ./out/test.o
	sudo ./out/stepper_test.o