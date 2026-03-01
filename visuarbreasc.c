#include <stdio.h> 
#include <stdlib.h> 
#include "genea.h"

int main(int argc, char *argv[]){

    if (argc != 5) {
        fprintf(stderr, "Usage: %s fichier-personnes fichier-liens-parente identifiant fichier-dot\n", argv[0]);
        return 1;
    }

    char *fichier_personnes = argv[1];
    char *fichier_liens_parente = argv[2];
    int identifiant = atoi(argv[3]);
    char *fichier_dot = argv[4];



    tArbre arbre = ArbreLirePersonnesFichier(fichier_personnes);
    arbre = ArbreLireLienParenteFichier(arbre,fichier_liens_parente);

    ArbreAfficherAscendants(arbre,identifiant);
    ArbreEcrireAscendantsGV(arbre,identifiant,fichier_dot);


    ArbreLiberer(arbre);

    return 0;
}

