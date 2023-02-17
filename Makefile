PROG = adventure
SRCS = adventure.c rooms/rooms.c items/items.c 
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -g

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)