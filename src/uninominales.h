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

///  fonction trouvant un gagnant en 1 tour et appelant la procédure afficher_resultat() pour l'afficher
/// \param[in, out] tableau de type t_tab_int_dyn contenant les scores des candidats
/// \param[in,out] matrice_csv matrice de type t_mat_char_star_dyn contenant les informations du csv
/// \param[in,out] logfp flux de sortie
void trouver_gagnant_un_tour(t_tab_int_dyn * tableau, t_mat_char_star_dyn * matrice_csv, FILE *logfp);

///  fonction trouvant un gagnant en 2 tours et appelant la procédure afficher_resultat() pour l'afficher
/// \param[in, out] tableau de type t_tab_int_dyn contenant les scores des candidats
/// \param[in,out] matrice_csv matrice de type t_mat_char_star_dyn contenant les informations du csv
/// \param[in,out] logfp flux de sortie
void trouver_gagnant_deux_tour(t_tab_int_dyn * tableau, t_mat_char_star_dyn * matrice_csv, FILE *logfp);
#endif //REV_PARTY_UNINOMINALES_H
