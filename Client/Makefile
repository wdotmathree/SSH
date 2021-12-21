CFLAGS = -Wall -Og -g -lcrypto

files := $(wildcard *.c)

build: ${files}
	$(CC) ${files} $(CFLAGS) -o ssh

clean:
	rm *.o *.so ssh
