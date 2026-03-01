#ifndef IDENTITE_H
#define IDENTITE_H

#include <stdio.h> 

# define LG_DATE 10 // Nombre de caract ères d’une date sous la forme jj/mm/ aaaa

// Identit é d’une personne
struct sIdentite
{
int Identifiant ; // Identifiant unique
char * Nom ; // Nom (cha îne de caract ères allou ée dynamiquement )
char * Prenom ; // Prénom (cha îne de caract ères allou ée dynamiquement )
char Sexe ; // ’F’ ou ’M’
char DateNaissance [ LG_DATE +1]; // Date de naissance sous la forme jj/mm/ aaaa
};

// Type permettant de manipuler l’identit é d’une personne
typedef struct sIdentite * tIdentite ;

tIdentite IdentiteCreer(int Id, char *Nom, char *Prenom, char Sexe, char DateNais[]);
int IdentiteIdentifiant(tIdentite Identite);
char *IdentiteNom(tIdentite Identite);
char *IdentitePrenom(tIdentite Identite);
char IdentiteSexe(tIdentite Identite);
char *IdentiteDateNaissance(tIdentite Identite);
void IdentiteAfficher(tIdentite Identite);
void IdentiteLiberer(tIdentite Identite);
tIdentite IdentiteLiref(FILE *f);


#endif 



