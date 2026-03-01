#include <stdio.h> 
#include <stdlib.h> 
#include "identite.h"
#include "genea.h"


tArbre ArbreCreer(void) {

    tArbre arbre = malloc(sizeof(struct sArbre));
    if (arbre==NULL){
        return NULL;
    }

    arbre->pPremiere = NULL;
    arbre->pDerniere = NULL;

    return arbre;

}

void ArbreAfficher(tArbre Arbre) {

    if (Arbre==NULL){
        printf("l'arbre est vide\n");
        return;
    }


    struct sFiche *ficheactuelle = Arbre->pPremiere;

    while (ficheactuelle != NULL){
        
    // On affiche l'identité sur laquelle on est 
    IdentiteAfficher(ficheactuelle->Identite);
    
    // On affiche l'identité du père
    printf("\tPère : ");
    if ((ficheactuelle->pPere) != NULL){
        IdentiteAfficher((ficheactuelle->pPere)->Identite);
    } else {
        printf("inconnu\n");
    }
   
    // On affiche l'identité de la mère
    printf("\tMère : ");
    if ((ficheactuelle->pMere) != NULL){
        IdentiteAfficher((ficheactuelle->pMere)->Identite);
    } else {
        printf("inconnue\n");
    }

    // On passe à la fiche suivante dans l'arbre
    ficheactuelle = ficheactuelle->pSuivante;
    }

}


void ArbreAjouterPersonne(tArbre Arbre, tIdentite Identite){
    if (Arbre == NULL || Identite == NULL) {
        fprintf(stderr, "Erreur : Arbre ou Identite est NULL\n");
        return;
    }
    // Création de la fiche 
    struct sFiche *nouvellefiche = malloc(sizeof(struct sFiche));
    if (nouvellefiche == NULL){
        printf("erreur allocation memoire");
        return;
    }

    // Initialiser la nouvelle fiche
    nouvellefiche->Identite = Identite;
    nouvellefiche->pPere = NULL;
    nouvellefiche->pMere = NULL;
    nouvellefiche->pSuivante = NULL;

    if (Arbre->pPremiere == NULL && Arbre->pDerniere == NULL){
        Arbre->pPremiere = nouvellefiche;
        Arbre->pDerniere = nouvellefiche;
    }

    // On met l'arbre à jour : ajout la fiche à la fin de la liste de l'arbre
    (Arbre->pDerniere)->pSuivante = nouvellefiche;
    Arbre->pDerniere = nouvellefiche;

}
 void ArbreLiberer(tArbre Arbre) {


    // On parcourt chaque fiche de l'arbre
    struct sFiche *fiche_actuelle = (Arbre->pPremiere);
    struct sFiche *fiche_libree;
    while (fiche_actuelle != NULL){
    IdentiteLiberer(fiche_actuelle->Identite);

    // On sauvegarde la fiche pour ensuite la libérer après avoir accédé à la fiche suivante
    fiche_libree = fiche_actuelle ;

    // C'est la fiche suivante (flemme de rechanger le nom)
    fiche_actuelle = (fiche_actuelle->pSuivante);

    // On libère la fiche
    free(fiche_libree);

    }

    free(Arbre);


 }


tArbre ArbreLirePersonnesFichier(char Fichier[]) {

    FILE *fic = fopen(Fichier, "r");
    if (fic == NULL){
        perror("erreur ouverture du fichier");
        return NULL;
    }

    //Création d'un arbre vide
    tArbre arbre = ArbreCreer();
    if (arbre == NULL){
        fclose(fic);
        return NULL;
    }

    int Identifiant;
    char Nom[81];
    char Prenom[81];
    char Sexe;
    char Date_de_naissance[LG_DATE+1];
    tIdentite identite;


    while (fscanf(fic, "%d %s %s %c %s",&Identifiant,Nom,Prenom,&Sexe,Date_de_naissance) == 5){
    identite =  IdentiteCreer(Identifiant, Nom, Prenom, Sexe, Date_de_naissance);
    ArbreAjouterPersonne(arbre,identite);

    }

    fclose(fic);
    return arbre;


 }

void ArbreAjouterLienParente(tArbre Arbre, int IdEnfant, int IdParent, char Parente){

    struct sFiche *fiche_enfant = Arbre->pPremiere;
    struct sFiche *fiche_parent = Arbre->pPremiere;

    // Trouver la fiche du parent dans l'arbre
    while (fiche_parent != NULL){
    if (((fiche_parent->Identite)->Identifiant) == IdParent){
        break;
    }
    else {
        fiche_parent = fiche_parent->pSuivante;
    }
    }

    // Trouver la fiche de l'enfant dans l'arbre
    while (fiche_enfant != NULL){
    if (((fiche_enfant->Identite)->Identifiant) == IdEnfant){
        break;
    }
    else {
        fiche_enfant = fiche_enfant->pSuivante;
    }
    }

    if (fiche_enfant != NULL && fiche_parent != NULL){
        if (Parente == 'M'){
            fiche_enfant->pMere = fiche_parent;
        } else if (Parente == 'P') {
            fiche_enfant->pPere = fiche_parent;
        } else{
            fprintf(stderr, "Erreur le type de parentée n'est pas reconnue \n");
        }

    } else {
        if (fiche_enfant == NULL){
            fprintf(stderr, "Aucune fiche trouvée pour l'enfant d'id : %d\n",IdEnfant);
        }

        if (fiche_parent == NULL){
            fprintf(stderr, "Aucune fiche trouvée pour le parent d'id : %d\n",IdParent);
        }
    
    }

 }



int ArbreLireLienParentef(FILE *f, int *pIdEnfant, int *pIdParent, char *pParente){

    // On va retourner 0 au cas où les pointeurs sonr nuls ou le fichier n'est pas valide
    if (f == NULL || pIdEnfant == NULL || pIdParent == NULL || pParente == NULL){
        return 0;
    }

    int resultat = fscanf(f,"%d %d %c\n",pIdEnfant, pIdParent, pParente);
   
    // Si fscanf lit correctement trois éléments, retourne 1
     if (resultat == 3){
        return 1;
    } else {
        return 0; // Si fscanf retourne EOF ou lit moins de trois éléments, retourne 0

    }

}

tArbre ArbreLireLienParenteFichier(tArbre Arbre, char Fichier[]) {

    if (Arbre == NULL) {
        fprintf(stderr, "Erreur : L'arbre est NULL.\n");
        return NULL;
    }

    FILE *fic = fopen(Fichier,"r");

    if (fic == NULL){
        perror("Erreur lors de l'ouverture du fichier ");
        return NULL;
    }

    int id_enfant, id_parent;
    char parente;

    while ((ArbreLireLienParentef(fic,&id_enfant,&id_parent,&parente)) == 1){

        // On ajoute le lien de parenté à l'arbre que quand la fonction ArbreLireLienParentef() a bien fonctionner
        ArbreAjouterLienParente(Arbre,id_enfant,id_parent,parente); 

}

    fclose(fic);
    return Arbre;
    
}

void ArbreEcrireGV(tArbre Arbre, char Fichier[]){

    FILE *fic = fopen(Fichier,"w");
    if (fic==NULL){
        perror("erreur de l'ouverture du fichier");
        return;
    }

    fprintf(fic, "digraph {\n");
    fprintf(fic, "\trankdir = \"BT\";\n\n");
    fprintf(fic, "\tnode [shape=box, color=blue, fontname=\"Arial\",fontsize=10];");

    // Écriture des noeuds pour les hommes
    struct sFiche *fiche = Arbre->pPremiere;
    while (fiche != NULL){
    if ((fiche->Identite)->Sexe == 'M'){
        fprintf(fic, "%d [label = \"%s\\n%s\\n%s\"];\n",(fiche->Identite)->Identifiant,(fiche->Identite)->Nom,(fiche->Identite)->Prenom,(fiche->Identite)->DateNaissance);
    }

    fiche = fiche->pSuivante;
    }

    fprintf(fic,"\n");

    fiche = Arbre->pPremiere;
    // Écriture des noeuds pour les femmes
    fprintf(fic,"\tnode [color=green];\n");
    while (fiche != NULL){
    if ((fiche->Identite)->Sexe == 'F'){
        fprintf(fic, "%d [label = \"%s\\n%s\\n%s\"];\n",(fiche->Identite)->Identifiant,(fiche->Identite)->Nom,(fiche->Identite)->Prenom,(fiche->Identite)->DateNaissance);
    }

    fiche = fiche->pSuivante;
    }

    fprintf(fic,"\n");


    // Écriture des liens 
    fprintf(fic,"\tedge [dir=none];\n");
    fiche = Arbre->pPremiere;
    while (fiche!=NULL){
        if (fiche->pPere != NULL){
            fprintf(fic, "%d -> %d;\n",(fiche->Identite)->Identifiant, fiche->pPere->Identite->Identifiant);
        }
        if (fiche->pMere != NULL){
            fprintf(fic, "%d -> %d;\n",(fiche->Identite)->Identifiant, fiche->pMere->Identite->Identifiant);
        }
        fiche = fiche->pSuivante;
    }
    fprintf(fic, "}");
    fclose(fic);



}

//Fonction récursive pour afficher l'identité de la personne et de ses ascendants
void AfficherAscendants(struct sFiche *fiche, int niveau){
    if (fiche == NULL){
        return;
    }

    // On affiche les tabulations en fonction de la valeur du niveau
    for (int i=0; i<niveau; i++){
        printf("\t");
    }


    // On affiche ensuite l'identité de la personne
    IdentiteAfficher(fiche->Identite);

    // S'il a un père, alors on l'affiche et faisant l'appel récursif et en changeant le niveau
    if (fiche->pPere != NULL){
        AfficherAscendants(fiche->pPere,niveau+1);
    }

    if (fiche->pMere != NULL){
        AfficherAscendants(fiche->pMere,niveau+1);
    }

}

void ArbreAfficherAscendants(tArbre Arbre, int Identifiant){
    if (Arbre == NULL){
        fprintf(stderr, "Erreur l'arbre est NULL\n");
        return; 
    }

    int niveau = 0;
    struct sFiche *fiche = Arbre->pPremiere;
    struct sFiche *fiche_personne;

    while (fiche != NULL){

        if (fiche->Identite->Identifiant == Identifiant){
            fiche_personne = fiche;

            AfficherAscendants(fiche_personne,niveau); // On appelle la fonction récursive dès qu'on a trouvé la personne
            

            return; // On arrête directement la fonction, plus besoin de continuer
        }


        fiche = fiche->pSuivante;
    }

    // Si la fonction ne s'est pas arrêté cela veut dire que la personne n'a pas été trouvée 
    fprintf(stderr, "Erreur : la personne n'a pas été trouvée dans l'arbre");


}



// Fonction récursive
void EcrireAscendantsGV(FILE *fic, struct sFiche *fiche){

    if (fiche==NULL){
        return;
    }

    // On ecrit le noeud pour la personne
    if (fiche->Identite->Sexe == 'M'){
        fprintf(fic, "node [color=blue];\n");
    } else if (fiche->Identite->Sexe == 'F'){
        fprintf(fic, "node [color=green];\n");
    }
    fprintf(fic,"%d [label=\"%s\\n%s\\n%s\"];\n\n",fiche->Identite->Identifiant, fiche->Identite->Nom, fiche->Identite->Prenom, fiche->Identite->DateNaissance);

    if (fiche->pPere != NULL){
        fprintf(fic, "%d -> %d;\n",fiche->Identite->Identifiant, fiche->pPere->Identite->Identifiant);
        EcrireAscendantsGV(fic, fiche->pPere);
    }

    if (fiche->pMere != NULL){
        fprintf(fic, "%d -> %d;\n",fiche->Identite->Identifiant, fiche->pMere->Identite->Identifiant);
        EcrireAscendantsGV(fic, fiche->pMere);
    }

}


void ArbreEcrireAscendantsGV(tArbre Arbre, int Identifiant, char Fichier[]){

    if (Arbre == NULL) {
        fprintf(stderr, "Erreur : L'arbre est NULL.\n");
        return;
    }

    FILE *fic = fopen(Fichier,"w");
    if (fic == NULL){
        perror("Erreur d'ouverture du fichier");
        return;
    }

    fprintf(fic, "digraph {\n");
    fprintf(fic, "\trankdir=\"BT\";\n\n");
    fprintf(fic, "\tnode [shape=box,fontname=\"Arial\",fontsize=10];\n\n");
    fprintf(fic, "\tedge [dir=none];\n\n");


    struct sFiche *fiche = Arbre->pPremiere;
    //On cherche la personne
    while (fiche != NULL){
        if (fiche->Identite->Identifiant == Identifiant){
            EcrireAscendantsGV(fic, fiche);
            break;
        }
        fiche = fiche->pSuivante;
    }

    fprintf(fic, "}\n");
    fclose(fic);

}
























