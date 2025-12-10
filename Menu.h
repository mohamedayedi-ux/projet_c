#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"  
#include "GestionSalle.h"
#include "Reservation.h"
#include "Stats.h"
#include "FonctionsAux.h"
#include "Facture.h"

extern Salle salles[MAX_SALLES];
extern int nb_salles;
extern Reservation reservations[MAX_RES];
extern int nb_reservations;

void menu();

#endif 