#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "salles.h"

typedef struct {
    int id;
    char nom_client[50];
    Salle salle;
    char date[11];
    char heure_debut[6];
    char heure_fin[6];
    int nombre_personnes;
    float tarif;
    char statut[20];
} Reservation;

int ajouterReservation(int id, char* nom_client, char* nom_salle, char* date,
                       char* debut, char* fin, int nb_personnes);
void statistiquesCompletes();
void recommanderSalles(int nb_personnes, char* date, char* debut, char* fin);

#endif
