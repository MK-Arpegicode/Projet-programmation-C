#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "identite.h"
#include "genea.h"

int main(int argc, char *argv[]){

//On vérifie le nbre d'arguments
if (argc!=3){
    fprintf(stderr, "errerur argument");
    return 1;

}




// On lit les fichiers 
char *fichier_personne = argv[1];
char *fichier_parente = argv[2];


// On crée l'arbre grâce au fichier
tArbre arbre1 = ArbreLirePersonnesFichier(fichier_personne);
if (arbre1 == NULL) {
        fprintf(stderr, "Erreur lors de la lecture du fichier de personnes.\n");
        return 1;
    }

//On établit les liens de parenté
ArbreLireLienParenteFichier(arbre1,fichier_parente);

ArbreAfficher(arbre1);
ArbreLiberer(arbre1);
return 0;
}





