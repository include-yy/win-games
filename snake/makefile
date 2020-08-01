CC = gcc

CFLAGS = -I include -Wall

vpath %.c src/cursor src/massfunction src/snakeoperate
vpath %.h include
vpath %.c src

HEADS = $(notdir $(wildcard include/*.h))

CURSOR = $(notdir $(wildcard src/cursor/*.c))

MASS = $(notdir $(wildcard src/massfunction/*.c))

SNAKEOP = $(notdir $(wildcard src/snakeoperate/*.c))

MAIN = $(notdir $(wildcard src/*.c))

OBJS = $(patsubst %.c, %.o, $(CURSOR) $(MASS) $(SNAKEOP) $(MAIN))

TARGET = snakegame

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^

%o:%c
	$(CC) -c -o $@ $(CFLAGS) $<


.PHONY : clean

clean :
	rm -f $(OBJS)
