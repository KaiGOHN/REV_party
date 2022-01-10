.PHONY: all clean
CC = gcc
CFLAGS = -Wall -std=c99
#LDFLAGS = -lm -lgmp
TARGET = scrutin # nom de l'exécutable
OBJFILES = build/main.o build/lecture_csv.o build/utils_sd.o build/matrice_duel_arc.o build/elementliste.o build/liste.o build/uninominales.o build/condorcet_minimax.o build/condorcet_schulze.o
TARGET2 = verify_my_vote
OBJFILES2 = build/verify_my_vote.o

all: $(TARGET) $(TARGET2)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

$(TARGET2): $(OBJFILES2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJFILES2) $(LDFLAGS)

build/verify_my_vote.o: src/verify_my_vote.c
	$(CC) $(CFLAGS) -c src/verify_my_vote.c -o build/verify_my_vote.o $(LDFLAGS)

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o $(LDFLAGS)

build/lecture_csv.o : src/lecture_csv.c
	$(CC) $(CFLAGS) -c src/lecture_csv.c -o build/lecture_csv.o $(LDFLAGS)

build/utils_sd.o : src/utils_sd.c
	$(CC) $(CFLAGS) -c src/utils_sd.c -o build/utils_sd.o $(LDFLAGS)

build/matrice_duel_arc.o : src/matrice_duel_arc.c
	$(CC) $(CFLAGS) -c src/matrice_duel_arc.c -o build/matrice_duel_arc.o $(LDFLAGS)

build/elementliste.o : src/elementliste.c
	$(CC) $(CFLAGS) -c src/elementliste.c -o build/elementliste.o $(LDFLAGS)

build/liste.o : src/liste.c
	$(CC) $(CFLAGS) -c src/liste.c -o build/liste.o $(LDFLAGS)

build/uninominales.o : src/uninominales.c
	$(CC) $(CFLAGS) -c src/uninominales.c -o build/uninominales.o $(LDFLAGS)

build/condorcet_minimax.o : src/condorcet_minimax.c
	$(CC) $(CFLAGS) -c src/condorcet_minimax.c -o build/condorcet_minimax.o $(LDFLAGS)

build/condorcet_schulze.o : src/condorcet_schulze.c
	$(CC) $(CFLAGS) -c src/condorcet_schulze.c -o build/condorcet_schulze.o $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
