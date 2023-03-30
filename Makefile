CC       = gcc
CFLAGS   = -Wall
OBJFILES = dungeon.o main.o
TARGET   = dungeon

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~