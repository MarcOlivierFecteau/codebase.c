CFLAGS = -Wall -Wextra -Wpedantic -std=c2x -Wno-unused-function -ggdb -Isrc/
BUILD_DIR = build

.PHONY: all
all: make_build_dir linalg_generator generate_linalg linalg auto-format

auto-format: linalg
	clang-format -i linalg.h --style="file"

linalg: linalg.h
	$(CC) $(CFLAGS) -Os -x c -c linalg.h -o $(BUILD_DIR)/linalg.o

generate_linalg:
	./$(BUILD_DIR)/generate_linalg > linalg.h

linalg_generator: src/linalg_generator.c
	$(CC) $(CFLAGS) src/linalg_generator.c -o $(BUILD_DIR)/generate_linalg
	# $(CC) $(CFLAGS) -DUSE_TYPEDEFS src/linalg_generator.c -o generate_linalg

tests: make_build_dir tests/test_char_type.c
	$(CC) $(CFLAGS) tests/test_char_type.c -o $(BUILD_DIR)/test_char_type && ./build/test_char_type

make_build_dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)
