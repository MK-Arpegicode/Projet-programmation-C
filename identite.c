#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "identite.h"


tIdentite IdentiteCreer(int Id, char *Nom, char *Prenom, char Sexe, char DateNais[]) {
    tIdentite personne = malloc(sizeof(struct sIdentite));
    if (personne == NULL){
        return NULL;
    }

    personne->Identifiant = Id;

    //Alloue et copie le nom
    personne->Nom =  malloc(strlen(Nom)*sizeof(char) + 1);
    if (personne->Nom == NULL){
        free(personne->Nom);
        free(personne);
        return NULL;
    }
    strcpy(personne->Nom, Nom);


    //Alloue et copie le prénom
    personne->Prenom = malloc(strlen(Prenom)*sizeof(char) + 1);
    if (personne->Prenom == NULL){
        free(personne->Prenom);
        free(personne);
        return NULL;
    }
    strcpy(personne->Prenom, Prenom);

    personne->Sexe = Sexe;
    strncpy(personne->DateNaissance, DateNais,LG_DATE);
    personne->DateNaissance[LG_DATE]='\0';

    return personne;

}

int IdentiteIdentifiant(tIdentite Identite){
    return Identite->Identifiant;
}

char *IdentiteNom(tIdentite Identite){
    return Identite->Nom;
}

char *IdentitePrenom(tIdentite Identite){
    return Identite->Prenom;
}

char IdentiteSexe(tIdentite Identite){
    return Identite->Sexe;
}

char *IdentiteDateNaissance(tIdentite Identite){
    return Identite->DateNaissance;
}

void IdentiteAfficher(tIdentite Identite){
    printf("[%d] %s %s %c %s\n",Identite->Identifiant,Identite->Nom,Identite->Prenom,Identite->Sexe,Identite->DateNaissance);
}

void IdentiteLiberer(tIdentite Identite){
    free(Identite->Nom);
    free(Identite->Prenom);
    free(Identite);
}

tIdentite IdentiteLiref(FILE *f){

    if (f == NULL) 
        return NULL;


    int Identifiant;
    char Nom[81];
    char Prenom[81];
    char Sexe;
    char Date_de_naissance[LG_DATE+1];

    if ( (fscanf(f, "%d %s %s %c %s",&Identifiant,Nom,Prenom,&Sexe,Date_de_naissance)) != 5 )
        return NULL;

    tIdentite personne = IdentiteCreer(Identifiant, Nom, Prenom, Sexe, Date_de_naissance); 
    return personne;

    

}

