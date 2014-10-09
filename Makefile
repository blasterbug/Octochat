ifndef INCLUDE_PATH
	INCLUDE_PATH=./include
endif

ifndef LIB_PATH
	LIB_PATH=./lib
endif

all: server client tcp_client udp_client tcp_server tcp_server

tcp_client:
	gcc -I$(INCLUDE_PATH) ./src/tcp_client.cpp -o tcp_client -lstdc++ $(LIB_PATH)/libboost_system.a $(LIB_PATH)/libboost_thread.a -lpthread -lrt
udp_client:
	gcc -I$(INCLUDE_PATH) ./src/udp_client.cpp -o udp_client -lstdc++ $(LIB_PATH)/libboost_system.a $(LIB_PATH)/libboost_thread.a -lpthread -lrt
tcp_server:
	gcc -I$(INCLUDE_PATH) ./src/tcp_server.cpp -o tcp_server -lstdc++ $(LIB_PATH)/libboost_system.a $(LIB_PATH)/libboost_thread.a -lpthread -lrt
udp_server:
	gcc -I$(INCLUDE_PATH) ./src/udp_server.cpp -o udp_server -lstdc++ $(LIB_PATH)/libboost_system.a $(LIB_PATH)/libboost_thread.a -lpthread -lrt
server:
	gcc -I$(INCLUDE_PATH) ./src/sandbox/chat_server.cpp -o chat_server -lstdc++ $(LIB_PATH)/libboost_system.a
client:
	gcc -I$(INCLUDE_PATH) ./src/sandbox/chat_client.cpp -o chat_client -lstdc++ $(LIB_PATH)/libboost_system.a $(LIB_PATH)/libboost_thread.a -lpthread -lrt
doc:
	doxygen Doxyfile
doclatex: doc
	make -C ./doc/latex

clean:
	-rm ./chat_server
	-rm ./chat_client

cleandoc:
	-rm -r ./doc
