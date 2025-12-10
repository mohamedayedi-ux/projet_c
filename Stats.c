#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stats.h"

void statistiquesCompletes() {
    int choix;
    do {
        printf("\n=== MODULE STATISTIQUES ===\n");
        printf("1. Le chiffre d'affaires par salle\n");
        printf("2. Le nombre de reservations par mois\n");
        printf("3. La(s) salle(s) la(es) plus populaire(s)\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1: { 
                printf("\n--- Chiffre d'affaires par salle ---\n");
                for (int i = 0; i < nb_salles; i++) {
                    float total = 0;
                    for (int j = 0; j < nb_reservations; j++) {
                        if (strcmp(reservations[j].statut,"confirmee")==0 &&
                            strcmp(reservations[j].salle.nom, salles[i].nom)==0) {
                            total += reservations[j].tarif;
                        }
                    }
                    printf("%s : %.2f TND\n", salles[i].nom, total);
                }
                break;
            }

            case 2: {
                int mois, annee;
                printf("Entrez le mois (1-12) : ");
                scanf("%d", &mois);
                printf("Entrez l'annee : ");
                scanf("%d", &annee);
                getchar();
                int nb = compterReservationsParMois(mois, annee);
                printf("Nombre de reservations confirmees pour %02d/%04d : %d\n", mois, annee, nb);
                break;
            }

            case 3: {
                int mois, annee;
                printf("Entrez le mois (1-12) : ");
                scanf("%d", &mois);
                printf("Entrez l'annee : ");
                scanf("%d", &annee);
                getchar();
                afficherSallesPopulaires(mois, annee);
                break;
            }

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }

    } while (choix != 0);
}

void recommanderSalles(int nb_personnes, char date[11], char debut[6], char fin[6]) {
    printf("\n--- Salles disponibles pour %d personnes le %s de %s a %s ---\n",
           nb_personnes, date, debut, fin);

    int trouve = 0;

    for (int i = 0; i < nb_salles; i++) {
       
        if (salles[i].capacite >= nb_personnes &&
            salleDisponible(salles[i], date, debut, fin) == 1) {

            printf("%d. %s | Capacite: %d | Tarif: %.2f TND/h | Equipements: %s\n",
                   i + 1,
                   salles[i].nom,
                   salles[i].capacite,
                   salles[i].tarif_horaire,
                   salles[i].equipements);

            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucune salle disponible pour ce créneau.\n");
}
int compterReservationsParMois(int mois, int annee){
    int compteur=0;
    for(int i=0;i<nb_reservations;i++){
        int j,m,a;
        if(sscanf(reservations[i].date,"%d/%d/%d",&j,&m,&a)==3){
            if(m==mois && a==annee && strcmp(reservations[i].statut,"confirmee")==0){
                compteur++;
            }
        }
    }
    return compteur;
}
void afficherSallesPopulaires(int mois, int annee){
    printf("\n--- Salles les plus populaires pour %02d/%04d ---\n",mois,annee);
    int maxReservations=0;
    for(int i=0;i<nb_salles;i++){
        int compteur=0;
        for(int j=0;j<nb_reservations;j++){
            int j_date,m_date,a_date;
            if(sscanf(reservations[j].date,"%d/%d/%d",&j_date,&m_date,&a_date)==3){
                if(m_date==mois && a_date==annee && strcmp(reservations[j].salle.nom,salles[i].nom)==0 && strcmp(reservations[j].statut,"confirmee")==0){
                    compteur++;
                }
            }
        }
        if(compteur>maxReservations){
            maxReservations=compteur;
        }
    }
    if(maxReservations==0){
        printf("Aucune reservation pour ce mois.\n");
        return;
    }
    for(int i=0;i<nb_salles;i++){
        int compteur=0;
        for(int j=0;j<nb_reservations;j++){
            int j_date,m_date,a_date;
            if(sscanf(reservations[j].date,"%d/%d/%d",&j_date,&m_date,&a_date)==3){
                if(m_date==mois && a_date==annee && strcmp(reservations[j].salle.nom,salles[i].nom)==0 && strcmp(reservations[j].statut,"confirmee")==0){
                    compteur++;
                }
            }
        }
        if(compteur==maxReservations){
            printf("%s avec %d reservations\n",salles[i].nom,compteur);
        }
    }
}




