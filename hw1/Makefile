CC=g++
CPPFLAGS= -g -std=c++11
DBFLAGS= -DDEBUG
TESTFLAGS= -DTEST
LDFLAGS=

TARGET= junit-flexchar
CPP_FILES=$(wildcard *.cpp)
OBJS=${CPP_FILES:%.cpp=%.o}

TESTS_DIR= tests/

export PATH := tests:$(PATH)

all: $(TARGET)

palindrome.o: palindrome.cpp

simpleCharManager.o: simpleCharManager.cpp

flexCharManager.o: flexCharManager.cpp

# JUNIT TEST SIMPLE

junit-simplechar: junit-simplechar.o simpleCharManager.o
	$(CC) $(CPPFLAGS) junit-simplechar.o simpleCharManager.o -o $@
	valgrind --leak-check=full --show-leak-kinds=all ./junit-simplechar
	make clean

junit-simplechar.o: $(TESTS_DIR)junit-simplechar.cpp
	$(CC) $(CPPFLAGS) $(TESTFLAGS) $(TESTS_DIR)junit-simplechar.cpp -c -o junit-simplechar.o

# JUNIT TEST FLEXIBLE

junit-flexchar: junit-flexchar.o flexCharManager.o simpleCharManager.o
	$(CC) $(CPPFLAGS) junit-flexchar.o flexCharManager.o simpleCharManager.o -o $@
	valgrind --leak-check=full --show-leak-kinds=all ./junit-flexchar
	make clean

junit-flexchar.o: $(TESTS_DIR)junit-flexchar.cpp
	$(CC) $(CPPFLAGS) $(TESTFLAGS) $(TESTS_DIR)junit-flexchar.cpp -c -o junit-flexchar.o

# JUNIT PALINDROME

junit-palindrome: junit-palindrome.o
	$(CC) $(CPPFLAGS) junit-palindrome.o -o $@
	valgrind --leak-check=full --show-leak-kinds=all ./junit-palindrome
	make clean

junit-palindrome.o: tests/junit-palindrome.cpp
	$(CC) $(CPPFLAGS) $(TESTFLAGS) tests/junit-palindrome.cpp -c -o junit-palindrome.o

# CLEAN

clean:
	rm -f *.o
