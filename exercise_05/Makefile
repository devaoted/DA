SRCS = main.cpp sufftree.cpp
OBJ = ${SRCS:.cpp=.o}
NAME = a.out

CC = g++
CFLAGS = -Wall -Wextra -Werror --std=c++17
LIBS =

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)
