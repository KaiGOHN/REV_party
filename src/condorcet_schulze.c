//
// Created by loic on 10/01/2022.
//

#include "condorcet_schulze.h"

///  application de la méthode condorcet + schulze pour trouver un vainqueur
/// \param[in] liste_arc
/// \return l'id du gagnant (colonne)
int trouver_gagnant_condorcet_schulze(liste * liste_arc) {
    int nb_el= nbEltList(*liste_arc);
    Elementliste element;
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
        return -origine-1;
    } else {
        int trouve=0;
        while (!trouve && !emptyList(*liste_arc)) {
            delFrontList(liste_arc);
            nb_el= nbEltList(*liste_arc);
            i=1;
            pickEltList(*liste_arc,&element,0);
            origine = element.orig;
            candidats=1;
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
                trouve=1;
            }
        }
        return origine;
    }
}