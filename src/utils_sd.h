//
// Created by loic on 08/01/2022.
//

#ifndef REV_PARTY_UTILS_SD_H
#define REV_PARTY_UTILS_SD_H
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// \fn creer_matrice_char
/// \param[in,out] matrice_csv pointeur vers la structure de type t_mat_char_star_dyn contenant la matrice à initialiser
void creer_matrice_char(t_mat_char_star_dyn * matrice_csv);

/// \fn creer_matrice_int
/// \param[in,out] matrice_duels pointeur vers la structure de type t_mat_int_dyn contenant la matrice à initialiser
/// \param[in] nbLigne entier spécifiant le nombre de lignes de la matrice à initialiser
/// \param[in] nbCol nbLigne entier spécifiant le nombre de colonnes de la matrice à initialiser
void creer_matrice_int(t_mat_int_dyn * matrice_duel, int nbLigne, int nbCol);


#endif //REV_PARTY_UTILS_SD_H
