CFLAGS = -Wall -Wextra -Wpedantic -std=c2x -Wno-unused-function -ggdb -Isrc/

.PHONY: all
all: linalg_generator generate_linalg linalg auto-format

auto-format: linalg
	clang-format -i linalg.h --style="file"

linalg: linalg.h
	$(CC) $(CFLAGS) -Os -x c -c linalg.h

generate_linalg:
	./generate_linalg > linalg.h

linalg_generator: src/linalg_generator.c
	$(CC) $(CFLAGS) src/linalg_generator.c -o generate_linalg
	# $(CC) $(CFLAGS) -DUSE_TYPEDEFS src/linalg_generator.c -o generate_linalg

clean:
	rm *.o generate_linalg
