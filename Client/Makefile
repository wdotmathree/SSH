CFLAGS = -Wall -Og -g

objects := $(patsubst %.c,%.o,$(wildcard *.c))
files := $(wildcard *.c)

build: ${objects}
	gcc ${objects} -o ssh

%.o: %.c
	$(CC) -c $(CFLAGS) $(CXXFLAGS) $< -o $@

clean:
	rm *.o
