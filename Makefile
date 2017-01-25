## blue Makefile
## Anas Rchid. fall 2017

CC = gcc
RM = rm -f
EXEC = blue

CFLAGS = -ggdb -O2 -Wall -Wextra -pedantic -Wpadded 
LDFLAGS = -I. -lbluetooth

DEPS =
OBJS = main.o

ARGS = test

all: main
	@echo "finish."

main: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	@echo "cleaning up.."
	$(RM) $(OBJ) $(EXEC)
