CC=gcc
LDFLAGS+=-lm
SRC=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRC) )
BIN = test

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c  $<  


all: $(OBJS)
	$(CC)  $(INCLUDE_PATH)  -o $(BIN)  $(OBJS)  -lm $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf $(BIN)
