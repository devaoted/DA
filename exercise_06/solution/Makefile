CC=g++
CFLAGS=-std=c++17 -pedantic -g -Wall -Wextra -Wno-unused-variable
EXECUTABLE=solution
SRC=main.cpp super_alg.cpp
OBJ=$(SRC:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

super_alg.o: super_alg.hpp super_alg.cpp

main.o: super_alg.hpp

clean:
	rm -f *.o $(EXECUTABLE)