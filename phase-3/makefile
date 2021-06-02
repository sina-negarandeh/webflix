CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/admin.o: src/exception.hpp src/film.hpp src/user.hpp src/admin.hpp src/admin.cpp
	$(CC) $(CF) -c src/admin.cpp -o $(BUILD_DIR)/admin.o

$(BUILD_DIR)/command_handler.o: src/network.hpp src/command_handler.hpp src/command_handler.cpp
	$(CC) $(CF) -c src/command_handler.cpp -o $(BUILD_DIR)/command_handler.o

$(BUILD_DIR)/comment.o: src/comment.hpp src/comment.cpp
	$(CC) $(CF) -c src/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/customer.o: src/user.hpp src/exception.hpp src/customer.hpp src/customer.cpp
	$(CC) $(CF) -c src/customer.cpp -o $(BUILD_DIR)/customer.o

$(BUILD_DIR)/exception.o: src/exception.hpp src/exception.cpp
	$(CC) $(CF) -c src/exception.cpp -o $(BUILD_DIR)/exception.o

$(BUILD_DIR)/film.o: src/exception.hpp src/comment.hpp src/film.hpp src/film.cpp
	$(CC) $(CF) -c src/film.cpp -o $(BUILD_DIR)/film.o

$(BUILD_DIR)/film_recommender.o: src/film_recommender.hpp src/film_recommender.cpp
	$(CC) $(CF) -c src/film_recommender.cpp -o $(BUILD_DIR)/film_recommender.o

$(BUILD_DIR)/network.o: src/user.hpp src/customer.hpp src/publisher.hpp src/admin.hpp src/film.hpp src/exception.hpp src/network.hpp src/network.cpp
	$(CC) $(CF) -c src/network.cpp -o $(BUILD_DIR)/network.o

$(BUILD_DIR)/publisher.o: src/user.hpp src/film.hpp src/exception.hpp src/publisher.hpp src/publisher.cpp
	$(CC) $(CF) -c src/publisher.cpp -o $(BUILD_DIR)/publisher.o

$(BUILD_DIR)/user.o: src/exception.hpp src/film.hpp src/user.hpp src/user.cpp
	$(CC) $(CF) -c src/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/handlers.o: src/handlers.cpp src/command_handler.hpp src/film.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c src/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: src/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c src/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: src/main.cpp src/command_handler.hpp src/network.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c src/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/admin.o $(BUILD_DIR)/command_handler.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/customer.o $(BUILD_DIR)/exception.o $(BUILD_DIR)/film.o $(BUILD_DIR)/film_recommender.o $(BUILD_DIR)/network.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/user.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/admin.o $(BUILD_DIR)/command_handler.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/customer.o $(BUILD_DIR)/exception.o $(BUILD_DIR)/film.o $(BUILD_DIR)/film_recommender.o $(BUILD_DIR)/network.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/user.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
