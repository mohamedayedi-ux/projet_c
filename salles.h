#ifndef SALLES_H
#define SALLES_H

typedef struct {
    char nom[50];
    int capacite;
    float tarif_horaire;
    char equipements[200];
} Salle;

void ajouterSalle(char* nom, int capacite, float tarif_horaire, char* equipements);
void afficherSalles();

#endif
