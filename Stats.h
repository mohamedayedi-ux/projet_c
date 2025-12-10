#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h" 
#include "GestionSalle.h"
#include "Reservation.h"
#include "FonctionsAux.h"

extern Salle salles[MAX_SALLES];
extern int nb_salles;
extern Reservation reservations[MAX_RES];
extern int nb_reservations;


void statistiquesCompletes();
void recommanderSalles(int nb_personnes,char date[11],char debut[6],char fin[6]);
int compterReservationsParMois(int mois, int annee);
void afficherSallesPopulaires(int mois, int annee);

#endif 