all: Network.out

Network.out: main.o command_handler.o comment.o customer.o exception.o film.o network.o publisher.o user.o
	g++ main.o command_handler.o comment.o customer.o exception.o film.o network.o publisher.o user.o -o Network.out

main.o: command_handler.h network.h main.cpp
	g++ -c main.cpp

command_handler.o: network.h command_handler.h command_handler.cpp
	g++ -c command_handler.cpp

comment.o: comment.h comment.cpp
	g++ -c comment.cpp

customer.o: user.h exception.h customer.h customer.cpp
	g++ -c customer.cpp

exception.o: exception.h exception.cpp
	g++ -c exception.cpp

film.o: exception.h comment.h film.h film.cpp
	g++ -c film.cpp

network.o: user.h customer.h publisher.h film.h exception.h network.h network.cpp
	g++ -c network.cpp

publisher.o: user.h film.h exception.h publisher.h publisher.cpp
	g++ -c publisher.cpp

user.o: exception.h film.h user.h user.cpp
	g++ -c user.cpp

.PHONY: clean
clean:
	rm *.o 
	rm Network.out
