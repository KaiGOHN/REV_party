.PHONY: all clean
CC = gcc
CFLAGS = -Wall -std=c99
#LDFLAGS = -lm -lgmp
TARGET = scrutin # nom de l'exécutable
OBJFILES = build/main.o build/lecture_csv.o build/utils_sd.o build/matrice_duel.o

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o $(LDFLAGS)

build/lecture_csv.o : src/lecture_csv.c
	$(CC) $(CFLAGS) -c src/lecture_csv.c -o build/lecture_csv.o $(LDFLAGS)

build/utils_sd.o : src/utils_sd.c
	$(CC) $(CFLAGS) -c src/utils_sd.c -o build/utils_sd.o $(LDFLAGS)

build/matrice_duel.o : src/matrice_duel.c
	$(CC) $(CFLAGS) -c src/matrice_duel.c -o build/matrice_duel.o $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
