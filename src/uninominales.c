//
// Created by loic on 09/01/2022.
//

#include "uninominales.h"

void trouver_gagnant_un_tour(t_tab_int_dyn * tableau, t_mat_char_star_dyn * matrice_csv, FILE *logfp) {
    for (int i=0; i<tableau->dim; i++) {
        tableau->tab[i]=0;
    }
    int min_id=4;
    int min_val=10;
    for (int i=1; i<matrice_csv->nbRows; i++) {
        min_id=4;
        min_val=11;
        for (int j=4; j<matrice_csv->nbCol; j++) {
            if (atoi(matrice_csv->tab[i][j])<min_val) {
                min_id=j;
                min_val=atoi(matrice_csv->tab[i][j]);
            }
        }
        int nul=0;
        for (int j=4; j<matrice_csv->nbCol; j++) {
            if (atoi(matrice_csv->tab[i][j])==min_val && min_id!=j) {
                nul=1;
            }
        }
        if (!nul) {
            tableau->tab[min_id-4]=tableau->tab[min_id-4]+1;
        }
    }
    int max_id=0;
    int max_val=0;
    int somme_val=0;
    for (int i=0; i<tableau->dim; i++) {
        if (tableau->tab[i]>max_val) {
            max_id=i;
            max_val=tableau->tab[i];
        }
        somme_val=somme_val+tableau->tab[i];
    }
    int nb_votes_nuls=matrice_csv->nbRows-1-somme_val;

    afficher_resultat("uninominal à un tour", matrice_csv->tab[0][max_id+4], matrice_csv->nbCol-4, matrice_csv->nbRows-1, 100*max_val/somme_val, logfp);
    fprintf(logfp, "Nb votes nuls : %d\n", nb_votes_nuls);
    //printf("gagnant = %s\n", matrice_csv->tab[0][max_id+4]);
}

void trouver_gagnant_deux_tour(t_tab_int_dyn * tableau, t_mat_char_star_dyn * matrice_csv, FILE *logfp) {
    for (int i=0; i<tableau->dim; i++) {
        tableau->tab[i]=0;
    }
    int min_id;
    int min_val;
    int nul;
    for (int i=1; i<matrice_csv->nbRows; i++) {
        min_id=4;
        min_val=11;
        for (int j=4; j<matrice_csv->nbCol; j++) {
            if (atoi(matrice_csv->tab[i][j])<min_val) {
                min_id=j;
                min_val=atoi(matrice_csv->tab[i][j]);
            }
        }
        nul=0;
        for (int j=4; j<matrice_csv->nbCol; j++) {
            if (atoi(matrice_csv->tab[i][j])==min_val && min_id!=j) {
                nul=1;
            }

        }
        if (!nul) {
            tableau->tab[min_id-4]=tableau->tab[min_id-4]+1;
        }
    }
    int max_id=0;
    int max_val=0;
    int somme_val=0;
    for (int i=0; i<tableau->dim; i++) {
        if (tableau->tab[i]>max_val) {
            max_id=i;
            max_val=tableau->tab[i];
        }
        somme_val=somme_val+tableau->tab[i];
    }
    int nb_votes_nuls_t1=matrice_csv->nbRows-1-somme_val;
    if (2*max_val>somme_val) {
        //printf("gagnant = %s\n", matrice_csv->tab[0][max_id+4]);
        afficher_resultat("uninominal deux un tour, tour 1", matrice_csv->tab[0][max_id+4], matrice_csv->nbCol-4, matrice_csv->nbRows-1, 100*max_val/somme_val, logfp);

    } else {
        int gagnant_1= max_id;
        int gagnant_1_score=max_val;
        tableau->tab[max_id]=0;
        max_id=0;
        max_val=0;
        for (int i=0; i<tableau->dim; i++) {
            if (tableau->tab[i]>max_val) {
                max_id=i;
                max_val=tableau->tab[i];
            }
        }
        int gagnant_2= max_id;
        int gagnant_2_score=max_val;
        //printf("gagnant 1 = %s avec %d%c, gagnant 2= %s avec %d%c pour un total de %d voix \n", matrice_csv->tab[0][gagnant_1+4], 100*gagnant_1_score/somme_val, 37, matrice_csv->tab[0][gagnant_2+4], 100*gagnant_2_score/somme_val, 37, somme_val);
        afficher_resultat("uninominal à deux tours, tour 1", matrice_csv->tab[0][gagnant_1+4], matrice_csv->nbCol-4, matrice_csv->nbRows-1, 100*gagnant_1_score/somme_val, logfp);
        afficher_resultat("uninominal à deux tours, tour 1", matrice_csv->tab[0][gagnant_2+4], matrice_csv->nbCol-4, matrice_csv->nbRows-1, 100*gagnant_2_score/somme_val, logfp);
        fprintf(logfp, "Nb votes nuls au tour 1 : %d\n", nb_votes_nuls_t1);
        int tab_second_tour[2];
        tab_second_tour[0]=0;
        tab_second_tour[1]=0;
        for (int i=1; i<matrice_csv->nbRows; i++) {
            if (atoi(matrice_csv->tab[i][gagnant_1+4])<atoi(matrice_csv->tab[i][gagnant_2+4])) {
                tab_second_tour[0]=tab_second_tour[0]+1;
            } else if (atoi(matrice_csv->tab[i][gagnant_1+4])>atoi(matrice_csv->tab[i][gagnant_2+4])) {
                tab_second_tour[1]=tab_second_tour[1]+1;
            }
        }
        int nb_votes_nuls_t2=matrice_csv->nbRows-1-(tab_second_tour[0]+tab_second_tour[1]);

        if (tab_second_tour[0]>tab_second_tour[1]) {
            //printf("gagnant = %s\n", matrice_csv->tab[0][gagnant_1+4]);
            afficher_resultat("uninominal à deux tours, tour 2", matrice_csv->tab[0][gagnant_1+4], 2, matrice_csv->nbRows-1, 100*tab_second_tour[0]/(tab_second_tour[0]+tab_second_tour[1]), logfp);

        } else if (tab_second_tour[0]<tab_second_tour[1]) {
            //printf("gagnant = %s\n", matrice_csv->tab[0][gagnant_2+4]);
            afficher_resultat("uninominal à deux tours, tour 2", matrice_csv->tab[0][gagnant_2+4], 2, matrice_csv->nbRows-1, 100*tab_second_tour[1]/(tab_second_tour[0]+tab_second_tour[1]), logfp);
        } else {
            //printf("egalité entre %s et %s \n", matrice_csv->tab[0][gagnant_1+4], matrice_csv->tab[0][gagnant_2+4]);
            char egalite[strlen(matrice_csv->tab[0][gagnant_2+4])+ strlen(matrice_csv->tab[0][gagnant_1+4])+5];
            strcat(egalite, matrice_csv->tab[0][gagnant_1+4]);
            strcat(egalite, " et ");
            strcat(egalite, matrice_csv->tab[0][gagnant_2+4]);
            afficher_resultat("uninominal à deux tours, tour 2", egalite, 2, matrice_csv->nbRows-1, 100*tab_second_tour[1]/(tab_second_tour[0]+tab_second_tour[1]), logfp);

        }
        fprintf(logfp, "Nb votes nuls au tour 2 : %d \n", nb_votes_nuls_t2);
    }

}