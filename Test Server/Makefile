default: src/test_server.cpp src/test_client.cpp
	g++ src/test_server.cpp -o out/server -std=c++11 -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
	g++ src/test_client.cpp -o out/client -std=c++11 -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
	./out/server
