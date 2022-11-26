NAME := minitalk
SERVER := server
CLIENT := client

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g3

CLIENT_SOURCES := client.c
CLIENT_OBJECTS := $(CLIENT_SOURCES:%.c=%.o)

SERVER_SOURCES := server.c utils.c
SERVER_OBJECTS := $(SERVER_SOURCES:%.c=%.o)

all: $(NAME)

$(NAME): | $(SERVER) $(CLIENT)

$(CLIENT): $(CLIENT_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER): $(SERVER_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: | fclean all

.PHONY: all $(NAME) clean fclean re
