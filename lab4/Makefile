CC = gcc
CFLAGS = -g
LDFLAGS =

PROG = lab4.out
HDRS = btree.h queue.h
SRCS = main.c btree.c queue.c

# Object file from each source
OBJS = $(SRCS:.c=.o)

# Rule for main file
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

# Rules for each file

main.o : main.c btree.h

btree.o: btree.c btree.h

queue.o: queue.c queue.h btree.h

# Remove program and object file
clean:
	rm -f $(PROG) $(OBJS)

test:
	./$(PROG) ./test/in.txt

