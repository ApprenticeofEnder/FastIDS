CFLAGS = -Wall -g
LIBRARIES = -lpcap
BUILD_DIR = build
SRC_DIR = src
BINARY = fast-ids
OBJECTS = $(BUILD_DIR)/fast_ids.o
OBJECT_TARGETS = fast_ids.o

all: $(OBJECT_TARGETS)
	gcc -o $(BINARY) $(CFLAGS) $(LIBRARIES) $(OBJECTS)

fast_ids.o: $(SRC_DIR)/fast_ids.c
	gcc $(CFLAGS) -c $(SRC_DIR)/fast_ids.c -o $(BUILD_DIR)/fast_ids.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(BINARY)
