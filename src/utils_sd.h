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
void liberer_matrice_char(t_mat_char_star_dyn * matrice_csv);

/// \fn creer_matrice_int
/// \param[in,out] matrice_duels pointeur vers la structure de type t_mat_int_dyn contenant la matrice à initialiser
/// \param[in] nbLigne entier spécifiant le nombre de lignes de la matrice à initialiser
/// \param[in] nbCol nbLigne entier spécifiant le nombre de colonnes de la matrice à initialiser
void creer_matrice_int(t_mat_int_dyn * matrice_duel, int nbLigne, int nbCol);
void liberer_matrice_int(t_mat_int_dyn * matrice_duel);
void creer_tab_int(t_tab_int_dyn * tableau, int nbCol);
void liberer_tab_int(t_tab_int_dyn * tableau);
void afficher_matrice_duel(t_mat_int_dyn * t_tab, FILE *outfp);
void afficher_matrice_arc(t_mat_int_dyn * t_tab, FILE *outfp);
void afficher_infos_csv(t_mat_char_star_dyn * matrice_csv, int * type_csv, FILE *outfp);
void afficher_matrice_csv(t_mat_char_star_dyn * matrice_csv, FILE *outfp);
void afficher_resultat(char * mode_scrutin, char * gagnant, int nb_candidats, int nb_votants, float score, FILE * logfp);
#endif //REV_PARTY_UTILS_SD_H
