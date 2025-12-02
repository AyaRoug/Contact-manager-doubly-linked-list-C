#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Contact{
    char nom [50];   //un tableau n'est pas besoin de l'allocation dynamique
    char telephone [20];
    struct Contact * precedent ;
    struct Contact * suivant ;
}Contact;

typedef struct{
    Contact *tete ;
    Contact *queue ;
    int taille ;
}ListeContacts;

ListeContacts* creerListe(){
    ListeContacts *L=(ListeContacts*)malloc(sizeof(ListeContacts ));
    L->tete=NULL;
    L->queue=NULL;
    L->taille=0;
    return L;
}

void ajouterDebut(ListeContacts* liste, char* nom, char* tel){
    Contact *NOUVEAU =(Contact*)malloc(sizeof(Contact));
        strcpy(NOUVEAU->nom,nom);
        strcpy(NOUVEAU->telephone,tel);
    if(liste->tete == NULL){
        NOUVEAU->precedent=NULL;
        NOUVEAU->suivant=NULL;
        liste->tete = NOUVEAU ;
        liste->queue = NOUVEAU ;
    }else{
        NOUVEAU->precedent=NULL;
        NOUVEAU->suivant=liste->tete;
        liste->tete-> precedent = NOUVEAU ;
        liste->tete = NOUVEAU ;
    }
        liste->taille ++;
}

void ajouterFin(ListeContacts* liste, char* nom, char* tel){
        Contact *NOUVEAU =(Contact*)malloc(sizeof(Contact));
        strcpy(NOUVEAU->nom,nom);
        strcpy(NOUVEAU->telephone,tel);
         if(liste->tete == NULL){
            NOUVEAU->precedent=NULL;
            NOUVEAU->suivant=NULL;
            liste->tete = NOUVEAU ;
            liste->queue = NOUVEAU ;
        }else{
            NOUVEAU->suivant=NULL;
            NOUVEAU->precedent=liste->queue;
            liste->queue->suivant = NOUVEAU ;
            liste->queue = NOUVEAU ;
    }
        liste->taille ++;
}

void ajouterApres(ListeContacts* liste, char* nomCible, char* nom, char* tel){
         if (liste == NULL || liste->tete == NULL) {
        printf("Liste vide. Insertion impossible apres un contact cible.\n");
        return;
    }
    // 1. Allouer et initialiser
    Contact *NOUVEAU = (Contact*)malloc(sizeof(Contact));
    strcpy(NOUVEAU->nom, nom);
    strcpy(NOUVEAU->telephone, tel);

    // 2. Chercher le contact Cible
    Contact *courant = liste->tete;
    while (courant != NULL && strcmp(courant->nom, nomCible) != 0) {
        courant = courant->suivant;
    }
    // Si 'courant' est NULL, le contact cible n'est pas trouvé
    if (courant == NULL) {
        printf("Contact cible '%s' non trouve.\n", nomCible);
        free(NOUVEAU); // Libérer la memoire
        return;
    }
    // 3. Chaînage du nouveau contact
    NOUVEAU->precedent = courant;
    NOUVEAU->suivant = courant->suivant;

    // 4. Mettre à jour les pointeurs des voisins
    if (courant->suivant != NULL) {
        // Insertion au milieu ou début
        courant->suivant->precedent = NOUVEAU;
    } else {
        // Insertion après la Queue (courant était la Queue)
        liste->queue = NOUVEAU;
    }
    courant->suivant = NOUVEAU;
    liste->taille++;
    printf("Ajout: '%s' insere apres '%s'.\n", nom, nomCible);
}

void supprimerContact(ListeContacts* liste, char* nom){
    Contact *SUPP_NOUVEAU=NULL , *courant= liste->tete;
    if (liste == NULL || liste->tete == NULL) return;
    // On cherche le contact
    while (courant != NULL) {
        if (strcmp(courant->nom, nom) == 0) {
            SUPP_NOUVEAU = courant;
            break;
        }
        courant = courant->suivant;
    }
    if(SUPP_NOUVEAU==NULL){
        printf("contact '%s' non trouve \n",nom);
        return;
        }
      // On détache le contact

    // Cas A : C'est la Tête
    if (SUPP_NOUVEAU == liste->tete) {
        liste->tete =SUPP_NOUVEAU->suivant;
        if (liste->tete != NULL) {
            liste->tete->precedent = NULL;
        } else {
            liste->queue = NULL;
        }

    // Cas B : C'est la Queue
    }else if (SUPP_NOUVEAU == liste->queue) {
        liste->queue = SUPP_NOUVEAU->precedent;
        if (liste->queue != NULL) {
            liste->queue->suivant = NULL;
      }
    }
    // Cas C : C'est au Milieu
    else {
        SUPP_NOUVEAU->precedent->suivant = SUPP_NOUVEAU->suivant;
        SUPP_NOUVEAU->suivant->precedent = SUPP_NOUVEAU->precedent;
    }

    free( SUPP_NOUVEAU);
    liste->taille--;
}

Contact* rechercherContact(ListeContacts* liste, char* nom){
    Contact *REC_NOUVEAU=NULL , *courant = liste->tete;
    if (liste == NULL || liste->tete == NULL)
        return NULL;
    while(courant!=NULL){
        if(strcmp(courant->nom, nom)==0){
            REC_NOUVEAU=courant;
            return REC_NOUVEAU;
        }
        courant=courant->suivant;
    }
       if(REC_NOUVEAU==NULL){   // REC_NOUVEAU n'est pas trouvé
         printf("contact '%s' non trouve \n",nom);
         return NULL;
        }
}

void afficherListeAvant(ListeContacts* liste){
    Contact *courant=liste->tete;
    printf("[ ");
    while(courant!= NULL){
      printf("%s\t%s",courant->nom,courant->telephone);
      courant=courant->suivant;

    }
   printf(" ]\n");
}

void afficherListeArriere(ListeContacts* liste){
    Contact *courant=liste->queue;
    printf("[ ");
    while(courant!= NULL){
      printf("%s\t%s",courant->nom,courant->telephone);
      courant=courant->precedent;

    }
   printf(" ]\n");

}

void trierListe(ListeContacts* liste){
    if (liste->taille == 0 || liste->tete == NULL) return;

    Contact *i, *j;
    char temp_nom[50];
    char temp_telephone[20];
    // Boucle externe : itère de la tête jusqu'à la fin
    for (i = liste->tete; i != NULL; i = i->suivant) {
        // Boucle interne : trouve le plus petit élément restant
        for (j = i->suivant; j != NULL; j = j->suivant) {
            if (strcmp(i->nom, j->nom) > 0) {
                // 1. Sauvegarder les données de i
                strcpy(temp_nom, i->nom);
                strcpy(temp_telephone, i->telephone);
                // 2. Copier les données de j dans i
                strcpy(i->nom, j->nom);
                strcpy(i->telephone, j->telephone);
                // 3. Copier les données temporaires de i dans j
                strcpy(j->nom, temp_nom);
                strcpy(j->telephone, temp_telephone);
            }
        }
    }
    printf("La liste a ete triee par nom.\n");
}

void viderListe(ListeContacts* liste){
    if (liste->taille == 0 || liste->tete == NULL) return;

    Contact *courant = liste->tete;
    Contact *suivant_a_liberer;
    while (courant != NULL) {
        suivant_a_liberer = courant->suivant;
        free(courant);
        courant = suivant_a_liberer;
    }
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
}
int main()
{
    ListeContacts *liste1= creerListe();
    Contact *rech;

    printf("ETAPE 1: ajout de contacts\n");
    ajouterDebut(liste1, "aya", "060050");
    ajouterApres(liste1, "aya", "fatima", "0799435");
    ajouterFin(liste1, "anom", "0587665");

    afficherListeAvant(liste1);
    afficherListeArriere(liste1);
    printf("\n");
    printf("\ntri :");
    trierListe(liste1);
    afficherListeAvant(liste1);

    printf("suppresion de non= fatima :\n");
    supprimerContact(liste1, "fatima");
    afficherListeAvant(liste1);
    printf("\n");
    printf("RECHERCHE DE NOM :\n");
    rech = rechercherContact(liste1, "anom");
    if(rech!=NULL){
        printf("contact 'anom' trouve : %s - %s\n",rech->nom, rech->telephone);
    }else{
        printf("contact 'anom' non trouve\n");
    }
    printf("\n");
    printf("liberation de memoire");
    viderListe(liste1);
    return 0;
}
