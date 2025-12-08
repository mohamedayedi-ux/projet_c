#ifndef SALLES_H
#define SALLES_H

#define MAX_SALLES 20

typedef struct {
    char nom[50];
    int capacite;
    float tarif_horaire;
    char equipements[200];
} Salle;

extern Salle salles[MAX_SALLES];
extern int nb_salles;

void ajouterSalle(char* nom, int capacite, float tarif_horaire, char* equipements);
void afficherSalles();

#endif
