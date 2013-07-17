# set c compiler to gcc
CC = gcc

# use CFLAGS to set compile flags
# -g        compile with debug information
# -Wall     display all warnings
# -O0       use optimization level 0
# -std=c99  use the C99 standard language definition
CFLAGS = -g -Wall -O0 -std=c99

# use LDFLAGS to set linker flags
# -lm       link to libm (math library)
# LDFLAGS = -lm

# list project files
SOURCES = mult.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = mult

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
