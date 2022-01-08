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


/// \fn getargs
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
                *nom_fichier_csv = optarg;
                if (strcmp(*nom_fichier_csv, "-d") == 0) {
                    duels=1;
                }
                break;
            case 'd':
                duels=1;
                *nom_fichier_csv = optarg;
                if (strcmp(*nom_fichier_csv, "-i") == 0) {
                    ballots=1;
                }
                break;
            case 'o':
                *type_log=1;
                *nom_fichier_log = optarg;
                break;
            case 'm':
                *methode = optarg;
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
            case '?':
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
    char * nom_fichier_csv = NULL;
    char  * nom_fichier_log = NULL;
    char * methode = NULL;
    int type_csv = 0;
    int type_log = 0;
    int err_arg = getargs(argc, argv, &nom_fichier_csv,  &nom_fichier_log, &methode, &type_csv, &type_log);
    if (err_arg) {
        exit(EXIT_FAILURE);
    }
    printf("nom_fichier_csv = %s, nom_fichier_log = %s, methode = %s, type_csv = %d, type_log = %d \n", nom_fichier_csv,  nom_fichier_log, methode, type_csv, type_log);
    int nb_col=0;
    int nb_ligne=0;
    char delimiteur=',';
    lecture_csv(nom_fichier_csv, &delimiteur, type_csv, &nb_col, &nb_ligne);
    return 0;
}