CC = gcc
CFLAGS = -g
LDFLAGS =

PROG = lab3.out
HDRS = graph.h
SRCS = main.c graph.c

# Object file from each source
OBJS = $(SRCS:.c=.o)

# Rule for main file
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

# Rules for each file

main.o : main.c graph.h

graph.o: graph.c graph.h

# Remove program and object file
clean:
	rm -f $(PROG) $(OBJS)

test:
	./$(PROG) ./test/in.txt

