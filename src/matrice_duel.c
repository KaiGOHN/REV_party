//
// Created by loic on 08/01/2022.
//

#include "matrice_duel.h"
/// \fn remplir_matrice_duel
/// \param matrice_csv[in,out] un pointeur vers une structure de type t_mat_char_star_dyn contenant les éléments extraits du fichier csv
/// \param matrice_duel[in,out] un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice de duel
/// \param type_csv[in,out] un pointeur vers un entier spécifiant le type de fichier csv (0 duels, 1 ballots)
void remplir_matrice_duel(t_mat_char_star_dyn * matrice_csv, t_mat_int_dyn * matrice_duel, int type_csv) {
    if (!*type_csv) {
        for (int i=0; i< matrice_duel->nbRows; i++) {
            for (int j=0; j<matrice_duel->nbCol; j++) {
               matrice_duel->tab[i][j]=atoi(matrice_csv->tab[i+1][j]);
            }
        }
    }
    else {
        for (int i=0; i<matrice_duel->nbRows; i++) {
            for (int j = 0; j < matrice_duel->nbCol; j++) {
                if (i==j) {
                    matrice_duel->tab[i][i]=0;
                }
                else {
                    int win=0;
                    for (int k=1; k<matrice_csv->nbRows; k++) {

                        if (matrice_csv->tab[k][i+4][0]!= '\0' && matrice_csv->tab[k][j+4][0] != '\0' && atoi(matrice_csv->tab[k][i+4])>0 && atoi(matrice_csv->tab[k][j+4])>0 && atoi(matrice_csv->tab[k][i+4])<11 && atoi(matrice_csv->tab[k][j+4])<11 && atoi(matrice_csv->tab[k][i+4])<atoi(matrice_csv->tab[k][j+4])) {
                            win++;
                        }
                    }
                    matrice_duel->tab[i][j] = win;
                }

            }
        }


    }
    for (int i=0; i<matrice_duel->nbRows; i++) {
        for (int j=0; j<matrice_duel->nbCol; j++) {
            printf("%d ", matrice_duel->tab[i][j]);
        }
        printf("\n");
    }
}