_main:class.h class.cpp _main.cpp
	g++ -std=c++11 -g class.h class.cpp _main.cpp -o _main


#_485_msg.o:_485_msg.cpp _485_msg.h
#	arm-linux-gnueabi-g++ -std=c++11 -c _485_msg.cpp
#_APP_main.o:_APP_main.cpp _485_msg.o
#	arm-linux-gnueabi-g++ -std=c++11 -pthread -c _APP_main.cpp
