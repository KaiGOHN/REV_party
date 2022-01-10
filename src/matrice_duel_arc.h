//
// Created by loic on 08/01/2022.
//

#ifndef REV_PARTY_MATRICE_DUEL_ARC_H
#define REV_PARTY_MATRICE_DUEL_ARC_H
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "elementliste.h"
///  remplir_matrice_duel
/// \param matrice_csv[in,out] un pointeur vers une structure de type t_mat_char_star_dyn contenant les éléments extraits du fichier csv
/// \param matrice_duel[in,out] un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice de duel
/// \param type_csv[in,out] un pointeur vers un entier spécifiant le type de fichier csv (0 duels, 1 ballots)
void remplir_matrice_duel(t_mat_char_star_dyn * matrice_csv, t_mat_int_dyn * matrice_duel, int * type_csv);

///  remplir_matrice_arc fonction de remplissage de la matrice des arcs
/// \param[in,out] matrice_duel un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice de duel
/// \param matrice_arc un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice des arcs
/// \param liste_arcs un pointeur vers une liste qui va contenir la liste des arcs
void remplir_matrice_arc(t_mat_int_dyn * matrice_duel, t_mat_int_dyn * matrice_arc, liste * liste_arcs);

#endif //REV_PARTY_MATRICE_DUEL_ARC_H
