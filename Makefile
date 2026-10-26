NAME = codexion
CC = cc
INCLUDE = -Iinclude
CFLAGS = -Werror -Wall -Wextra -Wconversion -pthread -ggdb

VPATH = src utils
SRCS = src/01_main.c \
       src/02_check_input.c \
	   src/03_settings.c \
	   src/04_simulation.c \
	   src/05_routine.c \
	   src/monitoring.c \
	   src/scheduling.c \
       utils/cleanup_utils.c\
	   utils/ft_itoa.c\
	   utils/ft_split.c\
	   utils/int_utils.c\
	   utils/list_utils.c\
	   utils/memory_utils.c\
	   utils/mutex_utils.c \
	   utils/print_utils.c\
	   utils/routine_utils.c \
	   utils/string_utils.c\
	   utils/time_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

TEST_NAME = tests/tests

TEST_SRCS = tests/tests_main.c \
			tests/input_tests.c \
       		src/02_check_input.c \
       		utils/cleanup_utils.c\
	   		utils/ft_itoa.c\
			utils/ft_split.c\
			utils/int_utils.c\
			utils/list_utils.c\
			utils/print_utils.c\
			utils/string_utils.c\
			utils/memory_utils.c \
			utils/time_utils.c

TEST_OBJS = $(TEST_SRCS:.c=.o)

test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) -o $(TEST_NAME) $(INCLUDE)

clean:
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
    
fclean: clean
	@rm -f $(NAME)
	@rm -f codexion
	@rm -f $(TEST_NAME)
	@rm -f tests/tests
    
re: clean all