//
// Created by loic on 08/01/2022.
//

#ifndef REV_PARTY_UTILS_SD_H
#define REV_PARTY_UTILS_SD_H
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void creer_matrice_char(t_mat_char_star_dyn * matrice_csv);
void creer_matrice_int(t_mat_int_dyn * matrice_duel, int nbLigne, int nbCol);
void copy_matrice_char(t_mat_char_star_dyn * matrice_in, t_mat_char_star_dyn * matrice_out);

#endif //REV_PARTY_UTILS_SD_H
