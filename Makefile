## blue Makefile
## Anas Rchid. fall 2017
## Modified: 02/08/2017 - 00:31:56

CC = gcc
RM = rm -f
DRM = rm -fr
EXEC = blue

SRCDIR = src
OBJDIR = bin
DEPSDIR = include


SRC := $(shell find $(SRCDIR) -name '*.c')
OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEPS:= $(shell find $(DEPSDIR) -name '*.h')

CFLAGS = -ggdb -O2 -Wall -Wextra -pedantic -Wpadded 
LDFLAGS = -I. -lbluetooth -lm

# DEPS = remote.h host.h lib.h
# OBJS = main.o remote.o host.o

ARGS = test

all: main
	@echo -e "\nfinish."

main: build-dir $(OBJ)
	@echo -e "\nbuilding application core.."
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)

build-dir:
	@$(call make-dir)

define make-dir
	for dir in $(OBJDIR); \
	do \
	mkdir -p $$dir; \
	done
endef

object: $(OBJ)
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

remake: clean all
clean:
	@echo -e "\ncleaning up.."
	$(RM) $(OBJ) $(EXEC)
	$(DRM) $(OBJDIR)
	@echo ""
