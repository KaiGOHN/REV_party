//
// Created by loic on 08/01/2022.
//

#include "lecture_csv.h"

/// \fn lecture_csv
/// \param filename pointeur vers une chaine de caractères désignant le nom du fichier csv
/// \param delimiteur pointeur vers une chaine de caractères désignant le délimiteur utilisé dans le csv
/// \param matrice pointeur vers la structure de type t_mat_char_star_dyn contenant la matrice à remplir
void lecture_csv(char *filename, char *delimiteur, t_mat_char_star_dyn * matrice, int * type_csv) {
    FILE *fptr;
    if ((fptr = fopen(filename,"r")) == NULL){
        fprintf(stderr, "Erreur! lors de l'ouverture du fichier csv\n");
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
                if (*type_csv) {
                    if (champ > 3 && matrice->nbRows-1 > 0 && (atoi(matrice->tab[matrice->nbRows - 1][champ]) <= 0 ||
                                                                 atoi(matrice->tab[matrice->nbRows - 1][champ]) >
                                                                 (matrice->nbCol - 4))) {
                        char str[matrice->nbRows];
                        sprintf(str, "%d", matrice->nbCol - 4);
                        strcpy(matrice->tab[matrice->nbRows - 1][champ], str);
                    }
                } else {
                    if (matrice->nbRows-1>0 && matrice->nbRows-1 != champ && (atoi(matrice->tab[matrice->nbRows - 1][champ]) <= 0)) {
                        char str[matrice->nbRows];
                        sprintf(str, "%d", 0);
                        strcpy(matrice->tab[matrice->nbRows - 1][champ], str);
                    }
                }
                champ++;
                debut = pointeur_delim+1;

            }
            matrice->tab[matrice->nbRows-1][champ] = (char *) malloc(256);
            strcpy(matrice->tab[matrice->nbRows-1][champ], debut);
            matrice->tab[matrice->nbRows-1][champ][strcspn(matrice->tab[matrice->nbRows-1][champ], "\n")] = 0;
            if (*type_csv) {
                if (champ > 3 && matrice->nbRows-1 > 0 && (atoi(matrice->tab[matrice->nbRows - 1][champ]) <= 0 ||
                                                           atoi(matrice->tab[matrice->nbRows - 1][champ]) >
                                                           (matrice->nbCol - 4))) {
                    char str[matrice->nbRows];
                    sprintf(str, "%d", matrice->nbCol - 4);
                    strcpy(matrice->tab[matrice->nbRows - 1][champ], str);
                }
            } else {
                if (matrice->nbRows-1>0 && matrice->nbRows-1 != champ && (atoi(matrice->tab[matrice->nbRows - 1][champ]) <= 0)) {
                    char str[matrice->nbRows];
                    sprintf(str, "%d", 0);
                    strcpy(matrice->tab[matrice->nbRows - 1][champ], str);
                }
            }
            if (champ != matrice->nbCol-1) {
                fprintf(stderr, "fichier CSV mal formé (ligne %d)\n ", matrice->nbRows);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(fptr);
}