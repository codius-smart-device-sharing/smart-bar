default: src/test_server.cpp src/test_client.cpp
	g++ src/test_server.cpp -o out/server -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
	g++ src/test_client.cpp -o out/client -lcrypto -lssl -lpthread /usr/local/lib/libboost_thread.a
