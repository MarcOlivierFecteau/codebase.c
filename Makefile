CFLAGS = -Wall -Wextra -Wpedantic -std=c2x -Wno-unused-variable -ggdb -Isrc/

.PHONY: all
all: linalg_generator generate_linalg linalg

linalg: linalg.h
	$(CC) $(CFLAGS) -c linalg.h -o linalg.o

generate_linalg:
	./generate_linalg > linalg.h

linalg_generator: src/linalg_generator.c
	$(CC) $(CFLAGS) src/linalg_generator.c -o generate_linalg

clean:
	rm *.o generate_linalg
