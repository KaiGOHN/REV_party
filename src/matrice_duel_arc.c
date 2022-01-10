//
// Created by loic on 08/01/2022.
//

#include "matrice_duel_arc.h"
///  remplir_matrice_duel fonction de remplissage de la matrice des duels
/// \param matrice_csv[in,out] un pointeur vers une structure de type t_mat_char_star_dyn contenant les éléments extraits du fichier csv
/// \param matrice_duel[in,out] un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice de duel
/// \param type_csv[in,out] un pointeur vers un entier spécifiant le type de fichier csv (0 duels, 1 ballots)
void remplir_matrice_duel(t_mat_char_star_dyn * matrice_csv, t_mat_int_dyn * matrice_duel, int * type_csv) {
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

                        if (atoi(matrice_csv->tab[k][i+4])<atoi(matrice_csv->tab[k][j+4])) {
                            win++;
                        }
                    }
                    matrice_duel->tab[i][j] = win;
                }

            }
        }


    }
    }

///  remplir_matrice_arc fonction de remplissage de la matrice des arcs
/// \param[in,out] matrice_duel un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice de duel
/// \param matrice_arc un pointeur vers une structure de type t_mat_int_dyn qui va contenir la matrice des arcs
/// \param liste_arcs un pointeur vers une liste qui va contenir la liste des arcs
void remplir_matrice_arc(t_mat_int_dyn * matrice_duel, t_mat_int_dyn * matrice_arc, liste * liste_arcs) {
    int poids_arc;
    Elementliste elem;
    if (!emptyList(*liste_arcs)) {
        fprintf(stderr, "Probleme lors de la création de la liste des arcs\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<matrice_duel->nbRows; i++) {
        for (int j=0; j<matrice_duel->nbCol; j++) {
            poids_arc = (matrice_duel->tab[i][j]>matrice_duel->tab[j][i]) ? matrice_duel->tab[i][j] - matrice_duel->tab[j][i] : 0;
            matrice_arc->tab[i][j] = poids_arc;
            if (poids_arc != 0) {
                elem.orig=i;
                elem.dest=j;
                elem.poids=poids_arc;
                addTailList(liste_arcs,elem);
            }

        }
    }
    bubbleSortList(liste_arcs);
    }
