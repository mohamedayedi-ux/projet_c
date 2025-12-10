#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "Structures.h"
#include "FonctionsAux.h"
#include "GestionSalle.h"
#include "Reservation.h"
#include "Stats.h"
#include "Menu.h"
#include "facture.h"




Salle salles[MAX_SALLES];
int nb_salles = 0;
Reservation reservations[MAX_RES];
int nb_reservations = 0;


int main(){
    setlocale(LC_ALL,"");


    ajouterSalle("Mercure",10,10.0,"Wi-Fi");
    ajouterSalle("Venus",15,18.0,"Projecteur, Wi-Fi");
    ajouterSalle("Terre",20,25.0,"Projecteur, Wi-Fi, Tableau blanc");
    ajouterSalle("Mars",12,15.0,"Wi-Fi, Tableau blanc");
    ajouterSalle("Jupiter",30,30.0,"Projecteur, Wi-Fi, Tableau blanc");
    ajouterSalle("Saturne",18,20.0,"Wi-Fi, Tableau blanc");
    ajouterSalle("Uranus",8,12.0,"Wi-Fi");
    ajouterSalle("Neptune",10,15.0,"Projecteur");



    chargerReservations();

    menu();

    return 0;
}