#include <stdio.h>
#include <string.h>
#include "reservations.h"

Reservation reservations[MAX_RES];
int nb_reservations = 0;

int heureEnMinutes(const char* heure) {
    int h, m;
    sscanf(heure, "%d:%d", &h, &m);
    return h*60 + m;
}

int chevauche(const char* debut1, const char* fin1,
              const char* debut2, const char* fin2) {

    int d1 = heureEnMinutes(debut1);
    int f1 = heureEnMinutes(fin1);
    int d2 = heureEnMinutes(debut2);
    int f2 = heureEnMinutes(fin2);

    return (d1 < f2) && (d2 < f1);
}

int salleDisponible(Salle salle, const char* date, const char* debut, const char* fin){
    for(int i=0; i<nb_reservations; i++){
        if(strcmp(reservations[i].salle.nom, salle.nom)==0 &&
           strcmp(reservations[i].date, date)==0 &&
           strcmp(reservations[i].statut, "confirmee")==0 &&
           chevauche(reservations[i].heure_debut, reservations[i].heure_fin, debut, fin)){
            return 0;
        }
    }
    return 1;
}

float calculTarif(Salle salle, const char* debut, const char* fin){
    int minutes = heureEnMinutes(fin) - heureEnMinutes(debut);
    return (minutes / 60.0f) * salle.tarif_horaire;
}

int ajouterReservation(int id, char* nom_client, char* nom_salle,
                       char* date, char* debut, char* fin, int nb_personnes){

    Salle* salle = NULL;
    for(int i=0; i<nb_salles; i++){
        if(strcmp(salles[i].nom, nom_salle)==0){
            salle = &salles[i];
            break;
        }
    }

    if(!salle){
        printf("Salle introuvable.\n");
        return 0;
    }

    if(nb_personnes > salle->capacite){
        printf("Salle trop petite.\n");
        return 0;
    }

    if(!salleDisponible(*salle, date, debut, fin)){
        printf("Salle non disponible.\n");
        return 0;
    }

    Reservation res;
    res.id = id;
    strcpy(res.nom_client, nom_client);
    res.salle = *salle;
    strcpy(res.date, date);
    strcpy(res.heure_debut, debut);
    strcpy(res.heure_fin, fin);
    res.nombre_personnes = nb_personnes;
    res.tarif = calculTarif(*salle, debut, fin);
    strcpy(res.statut, "confirmee");

    reservations[nb_reservations++] = res;

    printf("Reservation ID %d confirmee.\n", id);

    return 1;
}

void annulerModifierReservation(){
    printf("Fonction annuler/modifier ici...\n");
}
