.PHONY: all re clean fclean

# Program name
NAME	= ircserv

# Compiler
CC		= c++
CFLAGS	= -Werror -Wextra -Wall -g3 -std=c++98

# Build files
INC_PATH	= ./includes/
INC			= -I $(INC_PATH)

SRC_PATH	= ./sources/
SRC			= $(wildcard $(SRC_PATH)*.cpp)

OBJ_PATH	= ./objects/
OBJ			= $(SRC:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)

LIB			= -lssl -lcrypto

# Build rule
all: $(OBJ_PATH) $(NAME)

# Object-building rules
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Program-building rule
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC) $(LIB)

# Cleaning rules
clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

# Remake
re: fclean all
