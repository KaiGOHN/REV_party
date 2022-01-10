//
// Created by loic on 08/01/2022.
//

#ifndef REV_PARTY_GLOBAL_H
#define REV_PARTY_GLOBAL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_arc_p{ /// arc pondéré
    int orig;
    int dest;
    int poids;
} t_arc_p;

typedef struct s_mat_char_dyn{
    char *** tab;
    int nbRows;
    int nbCol;
} t_mat_char_star_dyn;

typedef struct s_mat_dyn{
    int ** tab;
    int nbRows;
    int nbCol;
} t_mat_int_dyn;

typedef struct s_tab_dyn{
    int * tab;
    int dim;
} t_tab_int_dyn;

#endif //REV_PARTY_GLOBAL_H
