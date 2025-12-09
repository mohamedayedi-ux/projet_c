#include "gestion.h"

Salle salles[MAX_SALLES];
int nb_salles = 0;

void ajouterSalle(char* nom, int capacite, float tarif_horaire, char* equipements){
    if(nb_salles >= MAX_SALLES) return;
    strcpy(salles[nb_salles].nom, nom);
    salles[nb_salles].capacite = capacite;
    salles[nb_salles].tarif_horaire = tarif_horaire;
    strcpy(salles[nb_salles].equipements, equipements);
    nb_salles++;
}

void afficherSalles(){
    printf("\n--- Liste des salles ---\n");
    for(int i=0;i<nb_salles;i++){
        printf("%d. %s | Capacite: %d | Tarif: %.2f TND/h | Equipements: %s\n",
               i+1, salles[i].nom, salles[i].capacite, salles[i].tarif_horaire, salles[i].equipements);
    }
}
