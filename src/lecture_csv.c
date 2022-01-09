//
// Created by loic on 08/01/2022.
//

#include "lecture_csv.h"


void lecture_csv(char *filename, char *delimiteur, t_mat_char_star_dyn * matrice) {
    FILE *fptr;
    if ((fptr = fopen(filename,"r")) == NULL){
        printf("Error! opening file\n");
        exit(EXIT_FAILURE);
    }
    char ligne[1024];
    char *  pointeur_delim;
    char * debut;
    if (fgets(ligne, 1024, fptr)) {
        debut = ligne;
        while ((pointeur_delim = strpbrk(debut, delimiteur)) != NULL) {
            *pointeur_delim = 0;
            matrice->tab[0]= realloc(matrice->tab[0], (matrice->nbCol)*sizeof(char *));
            if (matrice->tab[0] == NULL) {
                fprintf(stderr, "erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
            matrice->tab[0][matrice->nbCol-1] = (char *) malloc(256);
            strcpy(matrice->tab[0][matrice->nbCol-1], debut);
            matrice->tab[0][matrice->nbCol-1][strcspn(matrice->tab[0][matrice->nbCol-1], "\n")] = 0;
            matrice->nbCol++;
            debut = pointeur_delim+1;
        }
        matrice->tab[0]= realloc(matrice->tab[0], (matrice->nbCol)*sizeof(char *));
        if (matrice->tab[0] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        matrice->tab[0][matrice->nbCol-1] = (char *) malloc(256);
        strcpy(matrice->tab[0][matrice->nbCol-1], debut);
        matrice->tab[0][matrice->nbCol-1][strcspn(matrice->tab[0][matrice->nbCol-1], "\n")] = 0;

        while (fgets(ligne, 1024, fptr)) {
            matrice->nbRows++;
            matrice->tab=realloc(matrice->tab, (matrice->nbRows)*sizeof(char **));
            if (matrice->tab == NULL) {
                fprintf(stderr, "erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
            matrice->tab[matrice->nbRows-1]= realloc(matrice->tab[matrice->nbRows-1], (matrice->nbCol)*sizeof(char *));
            if (matrice->tab[matrice->nbRows-1] == NULL) {
                fprintf(stderr, "erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
            int champ=0;
            debut = ligne;
            while ((pointeur_delim = strpbrk(debut, delimiteur)) != NULL) {
                *pointeur_delim = 0;
                matrice->tab[matrice->nbRows-1][champ] = (char *) malloc(256);
                strcpy(matrice->tab[matrice->nbRows-1][champ], debut);
                matrice->tab[matrice->nbRows-1][champ][strcspn(matrice->tab[matrice->nbRows-1][champ], "\n")] = 0;
                champ++;
                debut = pointeur_delim+1;
            }
            matrice->tab[matrice->nbRows-1][champ] = (char *) malloc(256);
            strcpy(matrice->tab[matrice->nbRows-1][champ], debut);
            matrice->tab[matrice->nbRows-1][champ][strcspn(matrice->tab[matrice->nbRows-1][champ], "\n")] = 0;
            if (champ != matrice->nbCol-1) {
                fprintf(stderr, "fichier CSV mal formé (ligne %d)\n ", matrice->nbRows);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(fptr);
    printf("li : %d et col : %d\n", matrice->nbRows, matrice->nbCol);
}