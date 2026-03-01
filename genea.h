#ifndef GENEA_H
#define GENEA_H

#include "identite.h"

// Arbre géné alogique
struct sArbre
{
struct sFiche * pPremiere ; // Adresse de la premi ère fiche
struct sFiche * pDerniere ; // Adresse de la derni ère fiche
};

// Fiche associ ée à chaque individu pré sent dans l’arbre
struct sFiche
{
tIdentite Identite ; // Acc ès aux informations de l’identit é de la personne
struct sFiche * pPere ; // Adresse de la fiche du père
struct sFiche * pMere ; // Adresse de la fiche de la mère
struct sFiche * pSuivante ; // Adresse de la fiche suivante
};

// Type permettant de manipuler un arbre généalogique
typedef struct sArbre * tArbre ;

//Les fonctions
tArbre ArbreCreer(void);
void ArbreAfficher(tArbre Arbre);
void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite);
void ArbreLiberer(tArbre Arbre);
tArbre ArbreLirePersonnesFichier(char Fichier[]);
void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente);
int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente);
tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]);
void ArbreEcrireGV(tArbre Arbre, char Fichier[]);
void ArbreAfficherAscendants(tArbre Arbre, int Identifiant);
void EcrireAscendantsGV(FILE *fic, struct sFiche *fiche);
void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]);

#endif


