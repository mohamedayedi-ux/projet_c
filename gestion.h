#ifndef GESTION_H
#define GESTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALLES 20
#define MAX_RES 100

typedef struct {
    char nom[50];
    int capacite;
    float tarif_horaire;
    char equipements[200];
} Salle;

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

// Variables globales externes
extern Salle salles[MAX_SALLES];
extern int nb_salles;
extern Reservation reservations[MAX_RES];
extern int nb_reservations;

// Déclarations de fonctions
void ajouterSalle(char* nom, int capacite, float tarif_horaire, char* equipements);
int ajouterReservation(int id, char* nom_client, char* nom_salle, char* date, char* debut, char* fin, int nb_personnes);
void afficherSalles();
void statistiquesCompletes();
void menu();

#endif
