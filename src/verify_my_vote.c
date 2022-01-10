//
// Created by loic on 10/01/2022.
//

#include "verify_my_vote.h"
#define STRLONG 30

///  recherche_csv
/// \param filename pointeur vers une chaine de caractères désignant le nom du fichier csv
/// \param delimiteur pointeur vers une chaine de caractères désignant le délimiteur utilisé dans le csv
/// \param matrice pointeur vers la structure de type t_mat_char_star_dyn contenant la matrice à remplir

void recherche_csv(char *filename, char *delimiteur, char * chaine) {
    FILE *fptr;
    if ((fptr = fopen(filename,"r")) == NULL){
        fprintf(stderr, "Erreur! lors de l'ouverture du fichier csv\n");
        exit(EXIT_FAILURE);
    }
    char ligne[1024];
    char *  pointeur_delim;
    char * debut;
    int nb_champs=0;
    int nb_champs_1=0;

    if (fgets(ligne, 1024, fptr)) {
        char ** tableau_0 = malloc(1* sizeof(char * ));
        if (tableau_0 == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        debut = ligne;
        while ((pointeur_delim = strpbrk(debut, delimiteur)) != NULL) {
            *pointeur_delim = 0;
            tableau_0 = realloc(tableau_0, (nb_champs+1)*sizeof(char*));
            if (tableau_0 == NULL) {
                fprintf(stderr, "erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
            tableau_0[nb_champs] = malloc(sizeof(char) * 256 );
            if (tableau_0[nb_champs] == NULL) {
                fprintf(stderr, "erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
            strcpy(tableau_0[nb_champs], debut);
            tableau_0[nb_champs][strcspn(tableau_0[nb_champs], "\n")] = 0;
            nb_champs++;
            debut = pointeur_delim+1;
        }

        tableau_0 = realloc(tableau_0, (nb_champs+1)*sizeof(char *));
        if (tableau_0 == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        tableau_0[nb_champs] = malloc(sizeof(char) * 256 );
        if (tableau_0[nb_champs] == NULL) {
            fprintf(stderr, "erreur d'allocation\n");
            exit(EXIT_FAILURE);
        }
        strcpy(tableau_0[nb_champs], debut);
        tableau_0[nb_champs][strcspn(tableau_0[nb_champs], "\n")] = 0;
        nb_champs++;
        char ** tableau_1 = malloc(nb_champs* sizeof(char * ));
        int trouve=0;
        while (fgets(ligne, 1024, fptr) && !trouve) {
            nb_champs_1=0;
            debut = ligne;
            while ((pointeur_delim = strpbrk(debut, delimiteur)) != NULL) {
                *pointeur_delim = 0;
                tableau_1[nb_champs_1] = malloc(sizeof(char) * 256 );
                if (tableau_1[nb_champs_1] == NULL) {
                    fprintf(stderr, "erreur d'allocation\n");
                    exit(EXIT_FAILURE);
                }
                if (nb_champs_1 == 3 && strcmp(debut, chaine)==0) {
                    trouve=1;
                }
                strcpy(tableau_1[nb_champs_1], debut);
                tableau_1[nb_champs_1][strcspn(tableau_1[nb_champs_1], "\n")] = 0;
                nb_champs_1++;
                debut = pointeur_delim+1;
            }
            tableau_1[nb_champs_1] = malloc(sizeof(char) * 256 );
            if (tableau_1[nb_champs_1] == NULL) {
                fprintf(stderr, "erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
            strcpy(tableau_1[nb_champs_1], debut);
            tableau_1[nb_champs_1][strcspn(tableau_0[nb_champs_1], "\n")] = 0;
            nb_champs_1++;
        }
        fclose(fptr);
        if (trouve) {
            for (int i=0; i<nb_champs;i++) {
                printf("%s=%s\n", tableau_0[i], tableau_1[i]);
            }
        }
        for (int i=0; i<nb_champs;i++) {
            free(tableau_0[i]);
            free(tableau_1[i]);
        }
        free(tableau_0);
        free(tableau_1);
    }
}

///   récupération des arguments de la ligne de commande
/// \param[in] argc le nombre de parmamètres passés au programme
/// \param[in] argv la liste des paramètresp passés au programme
/// \param[in,out] nom_electeur de type char ** pointant vers la chaine qui recevra le nom de l'electeur
/// \param[in,out] nom_fichier_ballot de type char ** pointant vers la chaine qui recevra le nom du fichier de ballot
/// \param[in,out] char_cle  de type char ** pointant vers la chaine qui recevra la cle
/// \return 1 si tous les arguments sont présents
int getargs(int argc, char **argv, char **nom_electeur,  char **nom_fichier_ballot, char **char_cle) {
    char c;
    int ballots=0;
    int nom=0;
    int cle=0;
    int err_arg=0;
    while ((c = getopt(argc, argv, "i:n:c:")) != -1 ) {
        switch (c) {
            case 'i':
                ballots=1;
                strcpy(*nom_fichier_ballot, optarg);
                break;
            case 'n':
                nom=1;
                strcpy(*nom_electeur, optarg);
                break;
            case 'c':
                cle=1;
                strcpy(*char_cle, optarg);
                break;
            default:
                fprintf(stderr, "Argument inconnu.\n");
                err_arg=1;
                break;
        }
    }
    if (!(nom && ballots && cle)) {
        fprintf(stderr, "Vous devez fournir un nom avec -n, un fichier avec -i et une cle avec -c.\n");
        err_arg=1;
    }

    return err_arg;
}

int int_pow(int x, int n)
{
    if (n==1) {
        return x;
    } else if (n%2==0) {
        return int_pow(x*x, n/2);
    } else {
        return x* int_pow(x*2, (n-1)/2);
    }
}

int main(int argc, char **argv) {
    char * nom_electeur = malloc(256*sizeof (char));
    char  * nom_fichier_ballot = malloc(256*sizeof (char));
    char * cle = malloc(256*sizeof (char));
    nom_electeur[0]='\0';
    nom_fichier_ballot[0]='\0';
    cle[0]='\0';
    int err_arg = getargs(argc, argv, &nom_electeur,  &nom_fichier_ballot, &cle);
    if (err_arg) {
        exit(EXIT_FAILURE);
    }
    char delimiteur = ',';
    strcat(nom_electeur, cle);

    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    sha256ofString((BYTE *)nom_electeur,hashRes); // hashRes contient maintenant le hash de l'item
    recherche_csv(nom_fichier_ballot , &delimiteur, hashRes);
    free(nom_electeur);
    free(nom_fichier_ballot);
    free(cle);



    return 0;
}