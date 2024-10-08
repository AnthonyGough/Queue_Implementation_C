CC=gcc
CPPFLAGS= -I. -Wall
DEPS = proto_header.h
OBJS := unbounded_queue.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

b_bufq: $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f b_bufq *.o