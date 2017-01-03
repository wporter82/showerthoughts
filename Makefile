CC=gcc
CFLAGS=-Wall
LDLIBS=-lcurl -ljson-c
TARGET=showerthoughts

all: $(TARGET)

debug: CFLAGS += -DDEBUG -ggdb3
debug: $(TARGET)

$(TARGET): $(TARGET).c

.PHONY : clean
clean:
	$(RM) $(TARGET)

