ifndef INCLUDE_PATH
	INCLUDE_PATH=./include
endif

ifndef LIB_PATH
	LIB_PATH=./lib
endif

all: server client

server:
	gcc -I$(INCLUDE_PATH) ./src/sandbox/chat_server.cpp -o chat_server -lstdc++ $(LIB_PATH)/libboost_system.a
client:
	gcc -I$(INCLUDE_PATH) ./src/sandbox/chat_client.cpp -o chat_client -lstdc++ $(LIB_PATH)/libboost_system.a $(LIB_PATH)/libboost_thread.a -pthread -lrt

clean:
	-rm ./chat_server
	-rm ./chat_client
