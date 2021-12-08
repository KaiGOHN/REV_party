.PHONY: all clean
CC = gcc
CFLAGS = -Wall -std=c99
OBJFILES = mainfile.o liste.o elementliste.o
TARGET = liste

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
