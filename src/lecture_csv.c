//
// Created by loic on 08/01/2022.
//

#include "lecture_csv.h"

void lecture_csv(char *filename, char *delimiteur, int type_csv, int * nb_col, int * nb_ligne) {
    FILE *fptr;
    *nb_col=0;
    *nb_ligne=0;
    if ((fptr = fopen(filename,"r")) == NULL){
        printf("Error! opening file\n");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    char ligne[1024];
    char *** matrice= malloc(1*sizeof(char **));
    if (matrice == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(1);
    }
    matrice[0]= malloc(1*sizeof(char*));
    if (matrice[0] == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(1);
    }
    if (fgets(ligne, 1024, fptr)) {
        *nb_ligne=*nb_ligne+1;
    }
    char *  pointeur_delim;
    char * debut;
    debut = ligne;
    while ((pointeur_delim = strpbrk(debut, ",")) != NULL) {
        *pointeur_delim = 0;
        matrice[0]= realloc(matrice[0], (*nb_col+1)*sizeof(char *));
        if (matrice[0] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(1);
        }
        matrice[0][*nb_col] = (char *) malloc(256);
        strcpy(matrice[0][*nb_col], debut);
        matrice[0][*nb_col][strcspn(matrice[0][*nb_col], "\n")] = 0;
        *nb_col=*nb_col+1;
        debut = pointeur_delim+1;
    }
    matrice[0]= realloc(matrice[0], (*nb_col+1)*sizeof(char *));
    if (matrice[0] == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(1);
    }
    matrice[0][*nb_col] = (char *) malloc(256);
    strcpy(matrice[0][*nb_col], debut);
    matrice[0][*nb_col][strcspn(matrice[0][*nb_col], "\n")] = 0;
    while (fgets(ligne, 1024, fptr)) {
        matrice=realloc(matrice, (*nb_ligne+1)*sizeof(char **));
        if (matrice == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(1);
        }
        matrice[*nb_ligne]= realloc(matrice[*nb_ligne], (*nb_col+1)*sizeof(char *));
        if (matrice[*nb_ligne] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(1);
        }
        int champ=0;
        debut = ligne;
        while ((pointeur_delim = strpbrk(debut, ",")) != NULL) {
            *pointeur_delim = 0;
            matrice[*nb_ligne][champ] = (char *) malloc(256);
            strcpy(matrice[*nb_ligne][champ], debut);
            matrice[*nb_ligne][champ][strcspn(matrice[*nb_ligne][champ], "\n")] = 0;
            champ++;
            debut = pointeur_delim+1;
        }
        matrice[*nb_ligne][champ] = (char *) malloc(256);
        strcpy(matrice[*nb_ligne][champ], debut);
        matrice[*nb_ligne][champ][strcspn(matrice[*nb_ligne][champ], "\n")] = 0;
        if (champ != *nb_col) {
            fprintf(stderr, "fichier CSV mal formé\n");
            printf("%d : ligne :%d \n", champ, *nb_ligne);
            //exit(1);
        }
        *nb_ligne=*nb_ligne+1;
    }
    fclose(fptr);
    printf("nb_col = %d, nb_ligne = %d\n", *nb_col, *nb_ligne);
    for (int i =0; i<*nb_ligne; i++) {
        for (int j=0; j<=*nb_col; j++) {
            printf("[%s]", matrice[i][j]);
        }
        printf("\n");
    }
    printf("[%s]", matrice[1][9]);
    printf("\n");
}