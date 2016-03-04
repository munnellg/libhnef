CC           = gcc
CFLAGS       = -fPIC -g -pedantic -Wall -Wextra -march=native -ggdb3
LDFLAGS      = -shared

SOURCES = $(shell echo libhnef/*.c)
HEADERS = $(shell echo libhnef/*.h)
OBJECTS = $(SOURCES:.c=.o)

TARGET = libhnef.so

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS) 
