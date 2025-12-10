#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"

void menu() {
    int choix;
    int nextId=nb_reservations+1;
    char buffer[50];

    do{
        printf("\n--- MENU ---\n1. Ajouter une reservation\n2. Afficher la liste des salles\n3. Afficher les statistiques\n4. Annuler ou modifier une reservation\n5. Quitter\nVotre choix : ");
        fgets(buffer,sizeof(buffer),stdin);
        sscanf(buffer,"%d",&choix);

        if(choix==1){
            char nom_client[50], nom_salle[50], date[11], debut[6], fin[6]; int nb_personnes;
            printf("Nom du client : "); fgets(nom_client,sizeof(nom_client),stdin); nettoyerChaine(nom_client);
            while(nom_client[0]=='\0'){
                printf("Le nom du client ne peut pas etre vide. Veuillez ressaisir : ");
                fgets(nom_client,sizeof(nom_client),stdin); nettoyerChaine(nom_client);
         
            }
            int extra;
            while (1) {
                printf("Nombre de personnes : ");
                        fgets(buffer, sizeof(buffer), stdin);
                    if (sscanf(buffer, "%d %c", &nb_personnes, &extra) == 1 && nb_personnes > 0) {
       
                        break;
                        }
                    printf("Erreur : entrez un nombre entier valide.\n");}            
            lireDate(date); {
            lireHeure(debut,"Heure debut");
            while( heureEnMinutes(debut)<480){
                printf("Erreur :l'heure de debut doit etre entre 08:00 et 23:00.\n");
                lireHeure(debut,"Heure debut"); 
            }
            lireHeure(fin,"Heure fin");
            while( heureEnMinutes(fin)>1439){
                printf("Erreur :l'heure de fin doit etre entre 08:00 et 23:59.\n");
                lireHeure(fin,"Heure fin");
            }

            
           
            while(heureEnMinutes(fin)<=heureEnMinutes(debut)){
                printf("Erreur : L'heure de fin doit etre apres l'heure de debut.\n");
                lireHeure(fin,"Heure fin");
            }
        }

            

            recommanderSalles(nb_personnes,date,debut,fin);
            printf("Choisir la salle (nom) : "); fgets(nom_salle,sizeof(nom_salle),stdin); nettoyerChaine(nom_salle);
            while (1) 
            {
                if (trouverSalle(nom_salle) != NULL) {
                    break; 
                }
                printf("Salle invalide. Veuillez ressaisir : ");
                fgets(nom_salle, sizeof(nom_salle), stdin);
                nettoyerChaine(nom_salle);
            }
            
            Salle *salle = trouverSalle(nom_salle);
            int minutes=heureEnMinutes(fin)-heureEnMinutes(debut);
            float tarif=(minutes/60.0f)*salle->tarif_horaire;
            printf("Estimation :\n%s | Date : %s | Heure : %s-%s | Nombre : %d Duree : %d h %d min | Cout estime : %.2f TND\n",
            salle->nom,date,debut,fin,nb_personnes,minutes/60,minutes%60,tarif);
            printf("1)Reserver \n2)Retour au menu \nVotre choix : "); fgets(buffer,sizeof(buffer),stdin);
            int choix2; sscanf(buffer,"%d",&choix2);
            if(choix2==1){
                
                if(salle){
                    
                    if(choix2==1){
                        ajouterReservation(nextId++,nom_client,nom_salle,date,debut,fin,nb_personnes);
                        genererFacture(reservations[nb_reservations-1]);  
                        sauvegarderReservations();
                        printf("Reservation ajoutee avec succes!\n");
                    }
                    else {
                        printf("Retour au menu principal.\n");
                    }
                }

            } else printf("Choix invalide!\n");

        } 
        else if(choix==2) afficherSalles();
        else if(choix==3) statistiquesCompletes();
              
        else if(choix==4) annulerModifierReservation();
        else if(choix==5) printf("Au revoir !\n");
        else printf("Choix invalide.\n");

    } while(choix!=5);
}