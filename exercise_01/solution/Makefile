CC=g++
CFLAGS=-std=c++17 -pedantic -g -Wall -Wextra -Wno-unused-variable
EXECUTABLE=solution
SRC=lab1.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

lab1.o: pair.hpp sort.hpp vector.hpp

clean:
	rm -f *.o $(EXECUTABLE)