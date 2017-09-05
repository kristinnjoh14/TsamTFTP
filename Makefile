CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=700 -O2 -Wall -Wextra -Wformat=2
OBJFKAGS = -c

all:
	$(CC) $(CFLAGS) ./src/tftpd.c -o tftpd

.DEFAULT: all
.PHONY: all


