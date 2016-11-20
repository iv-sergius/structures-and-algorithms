CC = gcc
CFLAGS = -g
LDFLAGS = 

PROG = generate.out
HDRS =
SRCS = generate_test.c

# Object file from each source
OBJS = $(SRCS:.c=.o)

# Rule for main file
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

# Rules for each file

generate_test.o: generate_test.c

# Remove program and object file
clean:
	rm -f core $(PROG) $(OBJS)


