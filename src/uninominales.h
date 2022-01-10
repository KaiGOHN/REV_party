//
// Created by loic on 09/01/2022.
//

#ifndef REV_PARTY_UNINOMINALES_H
#define REV_PARTY_UNINOMINALES_H
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "elementliste.h"
#include "utils_sd.h"
void trouver_gagnant_un_tour(t_tab_int_dyn * tableau, t_mat_char_star_dyn * matrice_csv, FILE *logfp);
void trouver_gagnant_deux_tour(t_tab_int_dyn * tableau, t_mat_char_star_dyn * matrice_csv, FILE *logfp);
#endif //REV_PARTY_UNINOMINALES_H
