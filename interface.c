#include <stdio.h>
#include <stdlib.h>
#include "gestion.h"
#include "interface.h"

void lireDate(char* date){
    char buffer[20];
    int j,m,a;
    do{
        printf("Date (JJ/MM/AAAA): ");
        fgets(buffer, sizeof(buffer), stdin);

        if(sscanf(buffer, "%d/%d/%d", &j, &m, &a) == 3 &&
           j>=1 && j<=31 && m>=1 && m<=12){
            sprintf(date, "%02d/%02d/%04d", j, m, a);
            break;
        }

        printf("Format invalide.\n");

    }while(1);
}

void lireHeure(char* heure, const char* msg){
    char buffer[20];
    int h,m;

    do{
        printf("%s (HH:MM): ", msg);
        fgets(buffer, sizeof(buffer), stdin);

        if(sscanf(buffer, "%d:%d", &h, &m) == 2 &&
           h>=0 && h<=23 && m>=0 && m<=59){
            sprintf(heure, "%02d:%02d", h, m);
            break;
        }

        printf("Format invalide.\n");

    }while(1);
}

void menu(){
    int choix;
    char buffer[50];
    int nextId = nb_reservations + 1;

    do{
        printf("\n--- MENU ---\n");
        printf("1. Ajouter une reservation\n");
        printf("2. Afficher salles\n");
        printf("3. Statistiques\n");
        printf("4. Quitter\n");

        printf("Votre choix : ");
        fgets(buffer, sizeof(buffer), stdin);
        choix = atoi(buffer);

        if(choix == 1){
            char nom[50], nom_salle[50], date[11], deb[6], fin[6];
            int nb;

            printf("Nom client : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = 0;

            printf("Nombre personnes : ");
            fgets(buffer, sizeof(buffer), stdin);
            nb = atoi(buffer);

            lireDate(date);
            lireHeure(deb, "Heure debut");
            lireHeure(fin, "Heure fin");

            printf("Nom de la salle : ");
            fgets(nom_salle, sizeof(nom_salle), stdin);
            nom_salle[strcspn(nom_salle, "\n")] = 0;

            ajouterReservation(nextId++, nom, nom_salle, date, deb, fin, nb);
        }
        else if(choix == 2){
            afficherSalles();
        }
        else if(choix == 3){
            statistiquesCompletes();
        }

    }while(choix != 4);
}
