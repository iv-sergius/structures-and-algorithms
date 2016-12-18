CC = gcc
CFLAGS = -g
LDFLAGS =

PROG = test.out
HDRS = ../tree.h ../queue.h
SRCS = test.c ../tree.c ../queue.c

# Object file from each source
OBJS = $(SRCS:.c=.o)

# Rule for main file
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

# Rules for each file

test.o : test.c ../tree.h ../queue.h

tree.o : ../tree.c ../tree.h

queue.o : ../queue.c ../queue.h

# Remove program and object file
clean:
	rm -f core $(PROG) $(OBJS)

test:
	./$(PROG)
