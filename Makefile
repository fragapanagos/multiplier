# set c compiler to gcc
CC = gcc

# use CFLAGS to set compile flags
# -g            compile with debug information
# -Wall         display all warnings
# -O0           use optimization level 0
# -std=gnu99    use the C99 standard language definition with gnu extensions
CFLAGS = -g -Wall -O0 -std=gnu99

# use LDFLAGS to set linker flags
# -lrt      link to librt (real time library)
LDFLAGS = -lrt

# list project files
SOURCES = mult.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = mult

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
