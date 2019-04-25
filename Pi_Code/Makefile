stepper: stepper_test.cpp Stepper_5v.cpp Stepper.cpp
	g++ -g -Wall -Werror -std=c++11 stepper_test.cpp Stepper_5v.cpp Stepper.cpp -o out/stepper_test -lwiringPi

test: test.cpp Stepper.cpp Stepper_5v.cpp SmartBar.cpp test_server.cpp
	g++ -g -Wall -Werror -std=c++11 Stepper.cpp Stepper_5v.cpp SmartBar.cpp test.cpp -o out/test -lwiringPi 

server: test_server.cpp Stepper.cpp Stepper_5v.cpp SmartBar.cpp test_server.cpp
	g++ -g -Wall -Werror -std=c++11 Stepper.cpp Stepper_5v.cpp SmartBar.cpp test_server.cpp -o out/server -lwiringPi -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a

client: test_client.cpp
	g++ test_client.cpp -o out/client -std=c++11 -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
