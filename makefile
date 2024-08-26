CC=gcc
CPPFLAGS= -I. -Wall
DEPS = proto_header.h
OBJS := bounded_queue.o queue_api.o helper_fncs.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

b_bufq: $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f b_bufq *.o