prefix = $(shell pwd)

all: boost server client

boost:
	wget http://downloads.sourceforge.net/project/boost/boost/1.56.0/boost_1_56_0.7z && \
	7z x ./boost_1_56_0.7z && \
	cd ./boost_1_56_0 && \
	./bootstrap.sh --prefix=$(prefix) --with-libraries=system,thread,date_time,regex,serialization && \
	./b2 install && \
	cd .. && \
	rm -r ./boost_1_56_0*

server:
	gcc -I./include/ ./src/chat_server.cpp -o chat_server -lstdc++ ./lib/libboost_system.a
client:
	gcc -I./include/ ./src/chat_client.cpp -o chat_client -lstdc++ ./lib/libboost_system.a ./lib/libboost_thread.a -pthread -lrt

clean:
	-rm ./chat_server
	-rm ./chat_client
