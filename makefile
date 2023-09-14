# Nom des exécutables à générer
CLIENT_EXEC = client
SERVER_EXEC = server

# Fichiers sources
CLIENT_SRC = client.c
SERVER_SRC = server.c

# Options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(CLIENT_EXEC) $(SERVER_EXEC)

$(CLIENT_EXEC): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_EXEC) $(CLIENT_SRC)

$(SERVER_EXEC): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_EXEC) $(SERVER_SRC)

clean:
	rm -f $(CLIENT_EXEC) $(SERVER_EXEC)

re: clean all

.PHONY: all clean re
