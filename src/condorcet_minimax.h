//
// Created by loic on 10/01/2022.
//

#ifndef REV_PARTY_CONDORCET_MINIMAX_H
#define REV_PARTY_CONDORCET_MINIMAX_H
#include "global.h"
#include "liste.h"
#include "elementliste.h"

/// application de la méthode condorcet + minmax pour trouver un vainqueur
/// \param[in] liste_arc
/// \return l'id du gagnant (colonne)
int trouver_gagnant_condorcet_minmax(liste * liste_arcs);
#endif //REV_PARTY_CONDORCET_MINIMAX_H
