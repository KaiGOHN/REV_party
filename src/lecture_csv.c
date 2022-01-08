//
// Created by loic on 08/01/2022.
//

#include "lecture_csv.h"


void lecture_csv(char *filename, char *delimiteur, int * nb_ligne, int * nb_col, t_mat_char_star_dyn * matrice) {
    FILE *fptr;
    *nb_ligne=0;
    *nb_col=0;
    if ((fptr = fopen(filename,"r")) == NULL){
        printf("Error! opening file\n");
        exit(EXIT_FAILURE);
    }
    char ligne[1024];
    matrice->tab[0]= malloc(1*sizeof(char*));
    if (matrice->tab[0] == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    if (fgets(ligne, 1024, fptr)) {
        *nb_ligne=*nb_ligne+1;
    }
    char *  pointeur_delim;
    char * debut;
    debut = ligne;
    while ((pointeur_delim = strpbrk(debut, delimiteur)) != NULL) {
        *pointeur_delim = 0;
        matrice->tab[0]= realloc(matrice->tab[0], (*nb_col+1)*sizeof(char *));
        if (matrice->tab[0] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        matrice->tab[0][*nb_col] = (char *) malloc(256);
        strcpy(matrice->tab[0][*nb_col], debut);
        matrice->tab[0][*nb_col][strcspn(matrice->tab[0][*nb_col], "\n")] = 0;
        *nb_col=*nb_col+1;
        debut = pointeur_delim+1;
    }
    matrice->tab[0]= realloc(matrice->tab[0], (*nb_col+1)*sizeof(char *));
    if (matrice->tab[0] == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    matrice->tab[0][*nb_col] = (char *) malloc(256);
    strcpy(matrice->tab[0][*nb_col], debut);
    matrice->tab[0][*nb_col][strcspn(matrice->tab[0][*nb_col], "\n")] = 0;
    while (fgets(ligne, 1024, fptr)) {
        matrice->tab=realloc(matrice->tab, (*nb_ligne+1)*sizeof(char **));
        if (matrice->tab == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        matrice->tab[*nb_ligne]= realloc(matrice->tab[*nb_ligne], (*nb_col+1)*sizeof(char *));
        if (matrice->tab[*nb_ligne] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        int champ=0;
        debut = ligne;
        while ((pointeur_delim = strpbrk(debut, delimiteur)) != NULL) {
            *pointeur_delim = 0;
            matrice->tab[*nb_ligne][champ] = (char *) malloc(256);
            strcpy(matrice->tab[*nb_ligne][champ], debut);
            matrice->tab[*nb_ligne][champ][strcspn(matrice->tab[*nb_ligne][champ], "\n")] = 0;
            champ++;
            debut = pointeur_delim+1;
        }
        matrice->tab[*nb_ligne][champ] = (char *) malloc(256);
        strcpy(matrice->tab[*nb_ligne][champ], debut);
        matrice->tab[*nb_ligne][champ][strcspn(matrice->tab[*nb_ligne][champ], "\n")] = 0;
        if (champ != *nb_col) {
            fprintf(stderr, "fichier CSV mal formé (ligne %d)\n ", *nb_ligne+1);
            exit(EXIT_FAILURE);
        }
        *nb_ligne=*nb_ligne+1;
    }
    fclose(fptr);
    *nb_col=*nb_col+1;
    printf("li : %d col : %d\n", *nb_ligne, *nb_col);
    for (int i =0; i<*nb_ligne; i++) {
        for (int j=0; j<*nb_col; j++) {
            printf("[%s]", matrice->tab[i][j]);
        }
        printf("\n");
    }
}