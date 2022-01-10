//
// Created by loic on 08/01/2022.
//

#ifndef REV_PARTY_LECTURE_CSV_H
#define REV_PARTY_LECTURE_CSV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "utils_sd.h"

/// \fn lecture_csv
/// \param filename pointeur vers une chaine de caractères désignant le nom du fichier csv
/// \param delimiteur pointeur vers une chaine de caractères désignant le délimiteur utilisé dans le csv
/// \param matrice pointeur vers la structure de type t_mat_char_star_dyn contenant la matrice à remplir
void lecture_csv(char* filename, char * delimiteur, t_mat_char_star_dyn * matrice, int * type_csv);

#endif //REV_PARTY_LECTURE_CSV_H
