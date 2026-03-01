#include "identite.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


int main(){

    /*
    tIdentite personne1 = IdentiteCreer(30,"Messi","Leo",'M',"24/06/1987");

    int id_messi = IdentiteIdentifiant(personne1);
    printf("Identifiant de Messi: %d\n", id_messi);

    char *nom = IdentiteNom(personne1);
    printf("son nom est : %s\n",nom);

    char *prenom = IdentitePrenom(personne1);
    printf("son prenom est : %s\n",prenom);

    char sexe = IdentiteSexe(personne1);
    printf("son sexe est : %c\n",sexe);

    char *datenais = IdentiteDateNaissance(personne1);
    printf("date de naissance : %s\n",datenais);

    IdentiteAfficher(personne1);

    IdentiteLiberer(personne1);
    */

    FILE *fic = fopen("personne.ind","r");
    tIdentite personne = IdentiteLiref(fic);

    char *nom = IdentiteNom(personne);
    printf("son nom est : %s\n",nom);
    

    IdentiteLiberer(personne);

    return 0;
}


