CC=gcc
CFLAGS=-Wall
LIBS=-lcurl -ljson-c
TARGET=showerthoughts

all: $(TARGET)

debug: CFLAGS += -DDEBUG -ggdb3
debug: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c $(CFLAGS) $(LIBS) 

.PHONY : clean
clean:
	$(RM) $(TARGET)

