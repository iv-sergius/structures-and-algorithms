CC = gcc
CFLAGS = -g
LDFLAGS =

PROG = lab1.out
HDRS = stack.h
SRCS = main.c stack.c

# Object file from each source
OBJS = $(SRCS:.c=.o)

# Rule for main file
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

# Rules for each file

main.o : main.c stack.h

stack.o: stack.c stack.h

# Remove program and object file
clean:
	rm -f core $(PROG) $(OBJS)

test:
	$(PROG) ./test/1.pas

