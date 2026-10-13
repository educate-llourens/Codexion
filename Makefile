NAME = codexion
CC = cc
INCLUDE = -I/include
CFLAGS = -Werror -Wall -Wextra -Wconversion -pthread -ggdb

VPATH = src utils
SRCS = 01_main.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJS)
    
fclean: clean
	@rm -f $(NAME)
	@rm -f codexion
	@rm -f ./tests/test_codexion
    
re: clean all