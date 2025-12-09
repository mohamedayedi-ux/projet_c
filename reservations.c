#include "gestion.h"

Reservation reservations[MAX_RES];
int nb_reservations = 0;

int ajouterReservation(int id, char* nom_client, char* nom_salle, char* date, char* debut, char* fin, int nb_personnes){
    if(nb_reservations >= MAX_RES) return 0;

    // Chercher la salle
    Salle* salle = NULL;
    for(int i=0;i<nb_salles;i++){
        if(strcmp(salles[i].nom, nom_salle) == 0){
            salle = &salles[i];
            break;
        }
    }
    if(!salle) { printf("Salle introuvable.\n"); return 0; }
    if(nb_personnes > salle->capacite) { printf("Salle trop petite.\n"); return 0; }

    // Ajouter réservation
    Reservation res;
    res.id = id;
    strcpy(res.nom_client, nom_client);
    res.salle = *salle;
    strcpy(res.date, date);
    strcpy(res.heure_debut, debut);
    strcpy(res.heure_fin, fin);
    res.nombre_personnes = nb_personnes;
    res.tarif = ((float)(atoi(fin)-atoi(debut))) * salle->tarif_horaire; // simplifié
    strcpy(res.statut, "confirmee");

    reservations[nb_reservations++] = res;

    printf("Reservation ID %d confirmee : %s dans '%s'\n", res.id, res.nom_client, res.salle.nom);
    return 1;
}

void statistiquesCompletes(){
    printf("Fonction statistiques (à compléter)\n");
}
