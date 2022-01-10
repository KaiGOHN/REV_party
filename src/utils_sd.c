//
// Created by loic on 08/01/2022.
//

#include "utils_sd.h"

///  creer_matrice_char initialisation de la matrice contenant les infos du csv
/// \param[in,out] matrice_csv pointeur vers la structure de type t_mat_char_star_dyn contenant la matrice à initialiser
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
/*    matrice_csv->tab[0][0] = malloc(sizeof(char) * 256 );
    if (matrice_csv->tab[0][0] == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }*/
    matrice_csv->nbRows = 1;
    matrice_csv->nbCol = 1;
}

///  libération de la mémoire allouée à la matrice
/// \param[in] matrice_csv la matrice de type t_mat_char_star_dyn à libérer
void liberer_matrice_char(t_mat_char_star_dyn * matrice_csv) {
    for (int i=0; i<matrice_csv->nbRows; i++) {
        for (int j=0; j<matrice_csv->nbCol; j++) {
            free(matrice_csv->tab[i][j]);
        }
            free(matrice_csv->tab[i]);
    }
    free(matrice_csv->tab);
}

///  creer_matrice_int initialisation de la matrice contenant les duels ou les arcs
/// \param[in,out] matrice_duel pointeur vers la structure de type t_mat_int_dyn contenant la matrice à initialiser
/// \param[in] nbLigne entier spécifiant le nombre de lignes de la matrice à initialiser
/// \param[in] nbCol nbLigne entier spécifiant le nombre de colonnes de la matrice à initialiser
void creer_matrice_int(t_mat_int_dyn * matrice_duel, int nbLigne, int nbCol) {
    matrice_duel->tab = malloc(nbLigne*sizeof(int *));
    if (matrice_duel->tab  == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<nbLigne; i++) {
        matrice_duel->tab[i]= malloc(nbCol*sizeof(int));
        if (matrice_duel->tab[i] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
    }
    matrice_duel->nbRows = nbLigne;
    matrice_duel->nbCol = nbCol;
}

///  libération de la mémoire allouée à la matrice
/// \param[in] matrice_duel la matrice de type t_mat_int_dyn à libérer
void liberer_matrice_int(t_mat_int_dyn * matrice_duel) {
    for (int i=0; i<matrice_duel->nbRows; i++) {
        free(matrice_duel->tab[i]);
    }
    free(matrice_duel->tab);
}

///  creer_tab_int initialisation du tableau contenant les scores des méthodes uninominales
/// \param tableau de type t_tab_int_dyn à initialiser
/// \param nbCol entier définissant le nombre de colonnes avec lequel initialiser le tableau
void creer_tab_int(t_tab_int_dyn * tableau, int nbCol) {
    tableau->tab = malloc(nbCol*sizeof(int));
    if (tableau->tab  == NULL) {
        fprintf(stderr, "erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }
    tableau->dim = nbCol;
}

///  libération de la mémoire allouée à la matrice
/// \param[in] tableau le tableau à libérer
void liberer_tab_int(t_tab_int_dyn * tableau) {
    free(tableau->tab);
}

/*///
/// \param matrice_in
/// \param matrice_out
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

}*/

///  procédure d'affichage des résultats de la lecture du csv
/// \param[in] matrice_csv la matrice t_mat_char_star_dyn à afficher
/// \param[in,out] outfp le flux de sortie
void afficher_matrice_csv(t_mat_char_star_dyn * matrice_csv, FILE *outfp) {
    fprintf(outfp, "\nCONTENU CSV\n");
    for (int i=0; i<matrice_csv->nbRows; i++) {
        for (int j=0; j<matrice_csv->nbCol; j++){
            fprintf(outfp, "matrice[%d][%d]=%s\n", i, j, matrice_csv->tab[i][j]);
        }
        fprintf(outfp, "------------\n");
    }
}

///  procédure d'affichage des résultats de la construction de la matrice de duels
/// \param[in] matrice_duel la matrice t_mat_int_dyn à afficher
/// \param[in,out] outfp le flux de sortie
void afficher_matrice_duel(t_mat_int_dyn * matrice_duel, FILE *outfp) {
    fprintf(outfp, "\nMATRICE DES DUELS\n");
    for (int i=0; i<matrice_duel->nbRows; i++) {
        for (int j=0; j<matrice_duel->nbCol; j++){
            fprintf(outfp, "%d ", matrice_duel->tab[i][j]);
        }
        fprintf(outfp, "\n");
    }
}

///  procédure d'affichage des résultats de la construction de la matrice des arcs
/// \param[in] matrice_arc la matrice t_mat_int_dyn à afficher
/// \param[in,out] outfp le flux de sortie
void afficher_matrice_arc(t_mat_int_dyn * matrice_arc, FILE *outfp) {
    fprintf(outfp, "\nMATRICE DES ARCS\n");
    for (int i=0; i<matrice_arc->nbRows; i++) {
        for (int j=0; j<matrice_arc->nbCol; j++){
            fprintf(outfp, "%d ", matrice_arc->tab[i][j]);
        }
        fprintf(outfp, "\n");
    }
}

/// procédure d'affichage des infos pratiques sur le fichier csv
/// \param matrice_csv la matrice t_mat_char_star_dyn contenant les infos à afficher
/// \param type_csv le type de csv (duel 0 ou ballot 1)
/// \param outfp
void afficher_infos_csv(t_mat_char_star_dyn * matrice_csv, int * type_csv, FILE *outfp) {
    if (*type_csv) {
        fprintf(outfp, "\nINFOS CSV : \n");
        fprintf(outfp, "LIGNES : %d\n", matrice_csv->nbRows);
        fprintf(outfp, "COLONNES : %d\n", matrice_csv->nbCol);
        fprintf(outfp, "NB CANDIDATS : %d\n", matrice_csv->nbCol-4);
        fprintf(outfp, "NB VOTANTS : %d\n", matrice_csv->nbRows-1);
    } else
    {
        fprintf(outfp, "\nINFOS CSV : \n");
        fprintf(outfp, "LIGNES : %d\n", matrice_csv->nbRows);
        fprintf(outfp, "COLONNES : %d\n", matrice_csv->nbCol);
        fprintf(outfp, "NB CANDIDATS : %d\n", matrice_csv->nbCol);
        fprintf(outfp, "NB VOTANTS : %d\n",atoi(matrice_csv->tab[matrice_csv->nbRows-1][0]) + atoi(matrice_csv->tab[1][matrice_csv->nbCol-1]));
    }

}

/// procédure d'affichage des résultat
/// \param mode_scrutin chaine de caractère définissant le mode de scrutin
/// \param gagnant chaine de caractère définissant le nom de gagnant
/// \param nb_candidats entier definissant le nb de candidats
/// \param nb_votants entier  definissant le nb de votants
/// \param score flotant  definissant le score si uninominal
/// \param logfp le flux de sortie
void afficher_resultat(char * mode_scrutin, char * gagnant, int nb_candidats, int nb_votants, float score, FILE * logfp) {
    if (strcmp(mode_scrutin, "uninominal à deux tours, tour 1")==0 || strcmp(mode_scrutin, "uninominal à deux tours, tour 2")==0   || strcmp(mode_scrutin, "uninominal à un tour")==0 ) {
        if (logfp!=stdout) {
            fprintf(logfp, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.2f%c\n", mode_scrutin, nb_candidats, nb_votants, gagnant, score, 37);
            fprintf(stdout, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.2f%c\n", mode_scrutin, nb_candidats, nb_votants, gagnant, score, 37);
        } else {
            fprintf(logfp, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.2f%c\n", mode_scrutin, nb_candidats, nb_votants, gagnant, score, 37);

        }
        }
    else {
        if (logfp!=stdout) {
            fprintf(logfp, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", mode_scrutin, nb_candidats, nb_votants, gagnant);
            fprintf(stdout, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", mode_scrutin, nb_candidats, nb_votants, gagnant);

        } else {
            fprintf(logfp, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n", mode_scrutin, nb_candidats, nb_votants, gagnant);
        }
        }
    }
