#include <stdio.h> 
#include <stdlib.h>
#include "genea.h"

int main(int argc, char *argv[]){

    if (argc != 4) {
        fprintf(stderr, "Usage: %s fichier-personnes fichier-liens-parente fichier-dot\n", argv[0]);
        return 1;
    }

char *fichier_personnes = argv[1];
char *fichier_liens_parente = argv[2];
char *fichier_dot = argv[3];

tArbre arbre = ArbreLirePersonnesFichier(fichier_personnes);

arbre = ArbreLireLienParenteFichier(arbre,fichier_liens_parente);
ArbreEcrireGV(arbre,fichier_dot);

ArbreLiberer(arbre);
return 0;

}

