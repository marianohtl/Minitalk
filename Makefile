all: client server

client: client.c
	gcc -Wall -Wextra -Werror -g3 $< -o $@

server: server.c utils.c
	gcc -Wall -Wextra -Werror -g3 $^ -o $@

.PHONY: client server