CC = gcc
CFLAGS = -Wall -Wextra

SRCS = src/secondary_server.c src/client.c
OBJS = $(SRCS:.c=.o)
TARGETS = secondary_server.bin client.bin load_balancer.bin

all: $(TARGETS)

secondary_server.bin: src/secondary_server.c
	$(CC) $(CFLAGS) -c $< -o secondary_server.o
	$(CC) secondary_server.o graphdb/structs.h -o $@

client.bin: src/client.c
	$(CC) $(CFLAGS) -c $< -o client.o
	$(CC) client.o graphdb/structs.h -o $@

load_balancer.bin: src/load_balancer.c
	$(CC) $(CFLAGS) -c $< -o load_balancer.o
	$(CC) load_balancer.o graphdb/structs.h -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
