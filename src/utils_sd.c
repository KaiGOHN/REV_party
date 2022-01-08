//
// Created by loic on 08/01/2022.
//

#include "utils_sd.h"
void creer_matrice_char(t_mat_char_star_dyn * matrice_csv, int * nb_ligne, int * nb_col) {
    matrice_csv->tab = malloc(1*sizeof(char **));
    if (matrice_csv->tab  == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
    exit(1);
    }
    matrice_csv->nbRows = *nb_ligne;
    matrice_csv->nbCol = nb_col;
}
