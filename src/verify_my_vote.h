//
// Created by loic on 10/01/2022.
//

#ifndef REV_PARTY_VERIFY_MY_VOTE_H
#define REV_PARTY_VERIFY_MY_VOTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"

unsigned char * hexa_char_to_binary(char * chaine);

///  recherche_csv
/// \param filename pointeur vers une chaine de caractères désignant le nom du fichier csv
/// \param delimiteur pointeur vers une chaine de caractères désignant le délimiteur utilisé dans le csv
/// \param matrice pointeur vers la structure de type t_mat_char_star_dyn contenant la matrice à remplir
void recherche_csv(char *filename, char *delimiteur, char * chaine);
#endif //REV_PARTY_VERIFY_MY_VOTE_H
