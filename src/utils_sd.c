//
// Created by loic on 08/01/2022.
//

#include "utils_sd.h"
void creer_matrice_char(t_mat_char_star_dyn * matrice_csv) {
    matrice_csv->tab = malloc(1*sizeof(char **));
    if (matrice_csv->tab  == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    matrice_csv->tab[0]= malloc(1*sizeof(char*));
    if (matrice_csv->tab[0] == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    matrice_csv->nbRows = 1;
    matrice_csv->nbCol = 1;
}

void creer_matrice_int(t_mat_int_dyn * matrice_duels, int nbLigne, int nbCol) {
    matrice_duels->tab = malloc(nbLigne*sizeof(int *));
    if (matrice_duels->tab  == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<nbLigne; i++) {
        matrice_duels->tab[i]= malloc(nbCol*sizeof(int));
        if (matrice_duels->tab[i] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
    }
    matrice_duels->nbRows = nbLigne;
    matrice_duels->nbCol = nbCol;
}

void copy_matrice_char(t_mat_char_star_dyn * matrice_in, t_mat_char_star_dyn * matrice_out) {
    matrice_out->tab = malloc(matrice_in->nbRows*sizeof(char **));
    if (matrice_out->tab  == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    matrice_out->nbRows = matrice_in->nbRows;
    for (int i=0; i<matrice_in->nbRows; i++) {
        matrice_out->tab[i]= malloc(matrice_in->nbCol*sizeof(char*));
        if (matrice_out->tab[i] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        for (int j=0; j<matrice_in->nbCol; j++) {
            matrice_out->tab[i][j] = (char *) malloc(256);
            strcpy(matrice_out->tab[i][j], matrice_in->tab[i][j]);
        }
    }
    matrice_out->nbCol = matrice_in->nbCol;

}
