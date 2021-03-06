//
// Created by loic on 08/01/2022.
//
/// \file main.c
/// \author loic
/// \date 2022
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "lecture_csv.h"
#include "matrice_duel_arc.h"
#include "global.h"
#include "utils_sd.h"
#include "uninominales.h"
#include "condorcet_minimax.h"
#include "condorcet_schulze.h"

///  récupération des arguments de la ligne de commande
/// \param[in] argc le nombre de parmamètres passés au programme
/// \param[in] argv la liste des paramètresp passés au programme
/// \param[in,out] nom_fichier_csv pointeur de pointeur de char pour récuperer le nom du fichier csv
/// \param[in,out] nom_fichier_log pointeur de pointeur pour de char récuperer le nom du fichier de log
/// \param[in,out] methode pointeur de pointeur de char pour récuperer le nom de la méthode
/// \param[in,out] type_csv pointeur d'entier pour récuperer le type de fichier csv (0 duels, 1 ballots)
/// \param[in,out] type_log pointeur d'entier pour récuperer le type de log  (0 stdout, 1 fichier)
/// \return err_arg un entier=1 si une erreur s'est produite pendant la lecture des arguments, 0 sinon

int getargs(int argc, char **argv, char **nom_fichier_csv,  char **nom_fichier_log, char **methode, int * type_csv, int * type_log) {
    char c;
    int ballots=0;
    int duels=0;
    int err_arg=0;
    int methode_valide=0;
    while ((c = getopt(argc, argv, "i:d:o:m:")) != -1 ) {
        switch (c) {
            case 'i':
                ballots=1;
                strcpy(*nom_fichier_csv, optarg);
                if (strcmp(*nom_fichier_csv, "-d") == 0) {
                    duels=1;
                }
                break;
            case 'd':
                duels=1;
                strcpy(*nom_fichier_csv, optarg);
                if (strcmp(*nom_fichier_csv, "-i") == 0) {
                    ballots=1;
                }
                break;
            case 'o':
                *type_log=1;
                strcpy(*nom_fichier_log, optarg);
                break;
            case 'm':
                strcpy(*methode, optarg);
                if (strcmp(*methode, "uni1") == 0) {
                    methode_valide=1;
                } else {
                    if (strcmp(*methode, "uni2") == 0) {
                        methode_valide=1;
                    } else {
                        if (strcmp(*methode, "cm") == 0) {
                            methode_valide=1;
                        } else {
                            if (strcmp(*methode, "cs") == 0) {
                                methode_valide=1;
                            } else {
                                if (strcmp(*methode, "all") == 0) {
                                    methode_valide=1;
                                } else {
                                    methode_valide=0;
                                }
                            }
                        }
                    }
                }
                break;
            default:
                fprintf(stderr, "Argument inconnu.\n");
                err_arg=1;
                break;
        }
    }
    if (duels && ballots) {
        fprintf(stderr, "Les options -i et -d sont incompatibles.\n");
        err_arg=1;
    }
    if (duels) {
        *type_csv=0;
    }
    if (ballots) {
        *type_csv=1;
    }
    if (!duels && !ballots) {
        fprintf(stderr, "Une des options -i ou -d doit être spécifiée.\n");
        err_arg=1;
    }
    if (!methode_valide) {
        fprintf(stderr, "Vous devez spécifier une méthode valide, avec -m méthode ∈ {uni1, uni2, cm, cs, all}\n");
        err_arg=1;
    }
    if (duels && *methode != NULL) {
        if (strcmp(*methode, "uni1") == 0) {
            fprintf(stderr, "Méthode uni1 incompatible avec les duels .\n");
            err_arg=1;
        }
        if (strcmp(*methode, "uni2") == 0) {
            fprintf(stderr, "Méthode uni2 incompatible avec les duels .\n");
            err_arg=1;
        }
    }
    return err_arg;
}


int main(int argc, char **argv)
{
    char * nom_fichier_csv = malloc(256*sizeof (char));
    char  * nom_fichier_log = malloc(256*sizeof (char));
    char * methode = malloc(256*sizeof (char));
    nom_fichier_log[0]='\0';
    nom_fichier_csv[0]='\0';
    methode[0]='\0';
    int type_csv = 0;
    int type_log = 0;
    FILE *logfp;
    int err_arg = getargs(argc, argv, &nom_fichier_csv,  &nom_fichier_log, &methode, &type_csv, &type_log);
    if (err_arg) {
        exit(EXIT_FAILURE);
    }
    if (type_log) {
        FILE *fptr;
        if ((fptr = fopen(nom_fichier_log,"w")) == NULL){
            fprintf(stderr, "Erreur! lors de l'ouverture du fichier de log\n");
            exit(EXIT_FAILURE);
        } else {
            logfp=fptr;
            fprintf(stdout, "Fichier de sortie : %s\n", nom_fichier_log);
        }
    } else {
        logfp=stdout;
    }
    fprintf(logfp, "INFOS LIGNE COMMANDE : \nnom_fichier_csv = %s, nom_fichier_log = %s, methode = %s, type_csv = %d, type_log = %d \n", nom_fichier_csv,  nom_fichier_log, methode, type_csv, type_log);
    char delimiteur=',';
    t_mat_char_star_dyn matrice_csv;
    creer_matrice_char(&matrice_csv);
    lecture_csv(nom_fichier_csv, &delimiteur, &matrice_csv, &type_csv);
    afficher_infos_csv(&matrice_csv, &type_csv, logfp);
    afficher_matrice_csv(&matrice_csv, logfp);
    t_mat_int_dyn matrice_duel;
    if (!type_csv) {
        creer_matrice_int(&matrice_duel, matrice_csv.nbRows-1, matrice_csv.nbCol);
        remplir_matrice_duel(&matrice_csv, &matrice_duel, &type_csv);
    }
    else {
        creer_matrice_int(&matrice_duel, matrice_csv.nbCol-4, matrice_csv.nbCol-4);
        remplir_matrice_duel(&matrice_csv, &matrice_duel, &type_csv);
    }
    afficher_matrice_duel(&matrice_duel, logfp);
    t_mat_int_dyn matrice_arc;
    creer_matrice_int(&matrice_arc, matrice_duel.nbRows, matrice_duel.nbCol);
    liste liste_arcs;
    createList(&liste_arcs);
    remplir_matrice_arc(&matrice_duel, &matrice_arc, &liste_arcs);
    afficher_matrice_arc(&matrice_arc, logfp);
    fprintf(logfp, "\nLISTE DES ARCS");
    dumpList(liste_arcs,logfp);

    if (type_csv) {
        t_tab_int_dyn tableau;
        creer_tab_int(&tableau, matrice_csv.nbCol - 4);
        int nb_votants=matrice_csv.nbRows - 1;
        if (strcmp(methode, "all")==0) {


            trouver_gagnant_un_tour(&tableau, &matrice_csv, logfp);
            trouver_gagnant_deux_tour(&tableau, &matrice_csv, logfp);
            int id = trouver_gagnant_condorcet_minmax(&liste_arcs);

            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1) + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            } else {
                afficher_resultat("Condorcet minimax", matrice_csv.tab[0][id + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            }

            id = trouver_gagnant_condorcet_schulze(&liste_arcs);
            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1) + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            }
            else {
                afficher_resultat("Condorcet Schulze", matrice_csv.tab[0][id + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            }
        }
        else if (strcmp(methode, "cm")==0) {


            int id = trouver_gagnant_condorcet_minmax(&liste_arcs);

            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1) + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            } else {
                afficher_resultat("Condorcet minimax", matrice_csv.tab[0][id + 4], matrice_csv.nbCol - 4,
                                  nb_votants , 0, logfp);

            }
        } else if (strcmp(methode, "cs")==0) {


            int id = trouver_gagnant_condorcet_schulze(&liste_arcs);

            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1) + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            }
            else {
                afficher_resultat("Condorcet Schulze", matrice_csv.tab[0][id + 4], matrice_csv.nbCol - 4,
                                  nb_votants, 0, logfp);
            }
        } else if (strcmp(methode, "uni1")==0) {


            trouver_gagnant_un_tour(&tableau, &matrice_csv, logfp);
        } else {


            trouver_gagnant_deux_tour(&tableau, &matrice_csv, logfp);
        }

        liberer_tab_int(&tableau);

        }
    else {
        int nb = matrice_duel.tab[0][matrice_duel.nbRows - 1] + matrice_duel.tab[matrice_duel.nbRows - 1][0];
        // int nb = matrice_duel.nbCol ;
        if (strcmp(methode, "all")==0) {

            int id = trouver_gagnant_condorcet_minmax(&liste_arcs);
            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1)], matrice_csv.nbCol, nb, 0, logfp);
            } else {
                afficher_resultat("Condorcet minimax", matrice_csv.tab[0][id], matrice_csv.nbCol, nb, 0, logfp);
            }

            id = trouver_gagnant_condorcet_schulze(&liste_arcs);
            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1)], matrice_csv.nbCol, nb, 0, logfp);

            }
            else {
                afficher_resultat("Condorcet Schulze", matrice_csv.tab[0][id], matrice_csv.nbCol, nb, 0, logfp);

            }
            }
        else if (strcmp(methode, "cm")==0) {

            int id = trouver_gagnant_condorcet_minmax(&liste_arcs);
            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1)], matrice_csv.nbCol, nb, 0, logfp);
            } else {
                afficher_resultat("Condorcet minimax", matrice_csv.tab[0][id], matrice_csv.nbCol, nb, 0, logfp);
            }

                    }
        else  {

            int id = trouver_gagnant_condorcet_schulze(&liste_arcs);
            if (id<0) {
                afficher_resultat("Vainqueur de Condorcet", matrice_csv.tab[0][-(id+1)], matrice_csv.nbCol, nb, 0, logfp);
            }
            else {
                afficher_resultat("Condorcet Schulze", matrice_csv.tab[0][id], matrice_csv.nbCol, nb, 0, logfp);

            }
        }

        }
    liberer_matrice_char(&matrice_csv);
    liberer_matrice_int(&matrice_duel);
    liberer_matrice_int(&matrice_arc);
    if (type_log) fclose(logfp);
    free(nom_fichier_log);
    free(nom_fichier_csv);
    free(methode);

    return 0;
}
