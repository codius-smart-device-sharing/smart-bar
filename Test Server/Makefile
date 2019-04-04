all: test_server.cpp test_client.cpp
	g++ test_server.cpp -o server -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
	g++ test_client.cpp -o client -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
