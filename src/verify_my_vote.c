//
// Created by loic on 10/01/2022.
//

#include "verify_my_vote.h"
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

unsigned char hexa_char_to_binary(char * chaine) {
/*    int i=0;
    int len= strlen(chaine);
    int len_bin= int_pow(2,len);
    char * char_bin=malloc(len_bin*sizeof(char));
    char_bin[0]='\0';
    while (chaine[i]!='\0') {
        switch (chaine[i]) {
            case '0':
                strcat(char_bin, "0000");
                break;
            case '1':
                strcat(char_bin, "0001");
                break;
            case '2':
                strcat(char_bin, "0010");
                break;
            case '3':
                strcat(char_bin, "0011");
                break;
            case '4':
                strcat(char_bin, "0100");
                break;
            case '5':
                strcat(char_bin, "0101");
                break;
            case '6':
                strcat(char_bin, "0110");
                break;
            case '7':
                strcat(char_bin, "0111");
                break;
            case '8':
                strcat(char_bin, "1000");
                break;
            case '9':
                strcat(char_bin, "1001");
                break;
            case 'a':
                strcat(char_bin, "1010");
                break;
            case 'b':
                strcat(char_bin, "1011");
                break;
            case 'c':
                strcat(char_bin, "1100");
                break;
            case 'd':
                strcat(char_bin, "1101");
                break;
            case 'e':
                strcat(char_bin, "1110");
                break;
            case 'f':
                strcat(char_bin, "1111");
                break;
            default:
                break;
        }

        i++;
    }*/
    unsigned char myuchar=strtoul(chaine, NULL, 16);
    return myuchar;
}
int main(void) {
//    printf("Nom complet de l'électeur: ");
//    char nom_elect[];
//    scanf("%s", &nom);
//    printf("Nom du fichier de ballot: ");
//    char nom_ballot[];
//    scanf("%s", &nom);
//    printf("clef secrete: ");
//    char cle[];
//    scanf("%s", &cle);
//    unsigned char uchar;
//    uchar = hexa_char_to_binary(cle);

}