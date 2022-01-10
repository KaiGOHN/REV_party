//
// Created by loic on 10/01/2022.
//

#ifndef REV_PARTY_CONDORCET_SCHULZE_H
#define REV_PARTY_CONDORCET_SCHULZE_H
#include "global.h"
#include "liste.h"
#include "elementliste.h"

///  application de la méthode condorcet + schulze pour trouver un vainqueur
/// \param[in] liste_arc
/// \return l'id du gagnant (colonne)
int trouver_gagnant_condorcet_schulze(liste * liste_arcs);
#endif //REV_PARTY_CONDORCET_SCHULZE_H
