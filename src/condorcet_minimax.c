//
// Created by loic on 10/01/2022.
//

#include "condorcet_minimax.h"

int trouver_gagnant_condorcet_minmax(liste * liste_arc) {

    int nb_el= nbEltList(*liste_arc);
    Elementliste element;
    Elementliste element2;
    int i=1;
    int origine;
    pickEltList(*liste_arc,&element,0);
    origine = element.orig;
    int candidats=1;
    while (i<nb_el && candidats<=nb_el) {
        pickEltList(*liste_arc,&element,i);
        if (element.dest==origine) {
            i=0;
            origine=element.orig;
            candidats++;
        }
        i++;
    }
    if (candidats<=nb_el) {
        return origine;
    } else {
        pickEltList(*liste_arc,&element,nb_el-1);
        int destination=element.dest;
        int i=nb_el-2;
        int candidats=1;
        while (i>=0 && candidats<=nbEltList(*liste_arc)) {
            pickEltList(*liste_arc,&element2,i);
            if(element2.dest==destination) {
                delFrontList(liste_arc);
                pickEltList(*liste_arc,&element,nbEltList(*liste_arc)-1);
                destination=element.dest;
                candidats++;
                printf("candidats : %d \n", candidats);
            }
            i--;
        }
        return element.dest;
    }
}