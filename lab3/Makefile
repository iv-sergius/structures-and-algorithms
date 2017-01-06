CC = g++
CFLAGS = -g -std=c++11
LDFLAGS = 

PROG = lab3.out
HDRS = graph.h cycle.h
SRCS = main.c graph.c cycle.c

# Object file from each source
OBJS = $(SRCS:.c=.o)

# Rule for main file
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

# Rules for each file

main.o : main.c graph.h cycle.h

graph.o: graph.c graph.h cycle.h

cycle.o: cycle.c cycle.h

# Remove program and object file
clean:
	rm -f $(PROG) $(OBJS)

test:
	./$(PROG) ./test/in.txt

