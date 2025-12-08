#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "salles.h"

#define MAX_RES 100

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

extern Reservation reservations[MAX_RES];
extern int nb_reservations;

int heureEnMinutes(const char* heure);
int ajouterReservation(int id, char* nom_client, char* nom_salle,
                       char* date, char* debut, char* fin, int nb_personnes);
int salleDisponible(Salle salle, const char* date, const char* debut, const char* fin);
void annulerModifierReservation();

#endif
