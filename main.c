#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

// ----------------------------
// Constantes
// ----------------------------
#define MAX_SALLES 20  // Nombre maximum de salles
#define MAX_RES 100    // Nombre maximum de réservations

// ----------------------------
// Structures
// ----------------------------

// Structure Salle : contient toutes les informations d'une salle
typedef struct {
    char nom[50];          // Nom de la salle
    int capacite;          // Capacité maximale
    float tarif_horaire;   // Tarif par heure
    char equipements[200]; // Équipements disponibles
} Salle;

// Structure Reservation : contient toutes les informations d'une réservation
typedef struct {
    int id;                  // Identifiant unique
    char nom_client[50];     // Nom du client
    Salle salle;             // Salle réservée (copie de la structure Salle)
    char date[11];           // Date au format JJ/MM/AAAA
    char heure_debut[6];     // Heure de début HH:MM
    char heure_fin[6];       // Heure de fin HH:MM
    int nombre_personnes;    // Nombre de participants
    float tarif;             // Tarif total calculé
    char statut[20];         // Statut : "confirmee" ou "annulee"
} Reservation;

// ----------------------------
// Variables globales
// ----------------------------
Salle salles[MAX_SALLES];          // Tableau pour stocker toutes les salles
int nb_salles = 0;                 // Nombre de salles ajoutées

Reservation reservations[MAX_RES];  // Tableau pour stocker toutes les réservations
int nb_reservations = 0;           // Nombre de réservations

// ============================
// Fonctions auxiliaires
// ============================

// Convertit une heure "HH:MM" en minutes pour faciliter le calcul
int heureEnMinutes(const char* heure) {
    int h, m;
    sscanf(heure, "%d:%d", &h, &m);  // Lit l'heure et les minutes
    return h*60 + m;
}

// Vérifie si deux créneaux horaires se chevauchent
int chevauche(const char* debut1, const char* fin1, const char* debut2, const char* fin2) {
    int d1 = heureEnMinutes(debut1);
    int f1 = heureEnMinutes(fin1);
    int d2 = heureEnMinutes(debut2);
    int f2 = heureEnMinutes(fin2);
    return (d1 < f2) && (d2 < f1); // vrai si chevauchement
}

// Calcule le tarif total d'une réservation
float calculTarif(Salle salle, const char* debut, const char* fin) {
    int minutes = heureEnMinutes(fin) - heureEnMinutes(debut);
    return (minutes / 60.0) * salle.tarif_horaire;
}

// Vérifie si une salle est disponible pour un créneau donné
int salleDisponible(Salle salle, const char* date, const char* debut, const char* fin) {
    for(int i=0; i<nb_reservations; i++){
        // Si même salle, même date, statut confirmé et créneau chevauchant
        if(strcmp(reservations[i].salle.nom, salle.nom)==0 &&
           strcmp(reservations[i].date, date)==0 &&
           strcmp(reservations[i].statut,"confirmee")==0 &&
           chevauche(reservations[i].heure_debut, reservations[i].heure_fin, debut, fin)){
            return 0; // Non disponible
        }
    }
    return 1; // Disponible
}

// ============================
// Gestion des salles
// ============================

// Ajouter une salle dans le tableau
void ajouterSalle(char* nom, int capacite, float tarif_horaire, char* equipements){
    if(nb_salles>=MAX_SALLES) return; // Vérifie limite
    strcpy(salles[nb_salles].nom, nom);
    salles[nb_salles].capacite = capacite;
    salles[nb_salles].tarif_horaire = tarif_horaire;
    strcpy(salles[nb_salles].equipements, equipements);
    nb_salles++;
}

// Afficher toutes les salles disponibles
void afficherSalles(){
    printf("\n--- Liste des salles ---\n");
    for(int i=0;i<nb_salles;i++){
        printf("%d. %s | Capacite: %d | Tarif: %.2f TND/h | Equipements: %s\n",
               i+1, salles[i].nom, salles[i].capacite, salles[i].tarif_horaire, salles[i].equipements);
    }
}

// ============================
// Lecture sécurisée de date et heure
// ============================

// Lire une date au format JJ/MM/AAAA
void lireDate(char* date){
    char buffer[20];
    int j,m,a;
    do{
        printf("Date (JJ/MM/AAAA) : ");
        fgets(buffer,sizeof(buffer),stdin);
        if(sscanf(buffer,"%2d/%2d/%4d",&j,&m,&a)==3 && j>=1 && j<=31 && m>=1 && m<=12 && a>=2023){
            sprintf(date,"%02d/%02d/%04d", j,m,a);
            break;
        } else {
            printf("Format invalide. Reessayez.\n");
        }
    }while(1);
}

// Lire une heure au format HH:MM
void lireHeure(char* heure, const char* msg){
    char buffer[20];
    int h,m;
    do{
        printf("%s (HH:MM) : ", msg);
        fgets(buffer,sizeof(buffer),stdin);
        if(sscanf(buffer,"%d:%d",&h,&m)==2 && h>=0 && h<=23 && m>=0 && m<=59){
            sprintf(heure,"%02d:%02d", h,m);
            break;
        } else {
            printf("Format invalide. Reessayez.\n");
        }
    }while(1);
}

// ============================
// Gestion des réservations
// ============================

// Ajouter une réservation et générer facture
int ajouterReservation(int id, char* nom_client, char* nom_salle, char* date,
                       char* debut, char* fin, int nb_personnes){
    if(nb_reservations>=MAX_RES) return 0;

    // Chercher la salle dans le tableau
    Salle* salle = NULL;
    for(int i=0;i<nb_salles;i++){
        if(strcmp(salles[i].nom, nom_salle)==0){
            salle = &salles[i]; // pointeur vers la salle
            break;
        }
    }
    if(!salle){ printf("Salle introuvable.\n"); return 0;}
    if(nb_personnes>salle->capacite){ printf("Salle trop petite.\n"); return 0;}
    if(!salleDisponible(*salle,date,debut,fin)){ printf("Salle non disponible.\n"); return 0;}

    // Créer la réservation
    Reservation res;
    res.id = id;
    strcpy(res.nom_client, nom_client);
    res.salle = *salle; // copie de la salle
    strcpy(res.date,date);
    strcpy(res.heure_debut,debut);
    strcpy(res.heure_fin,fin);
    res.nombre_personnes = nb_personnes;
    res.tarif = calculTarif(*salle,debut,fin);
    strcpy(res.statut,"confirmee");

    reservations[nb_reservations++] = res; // Ajouter au tableau

    // Afficher confirmation
    printf("Reservation ID %d confirmee : %s dans '%s' le %s de %s a %s (%.2f TND)\n",
           res.id, nom_client, salle->nom, res.date, res.heure_debut, res.heure_fin, res.tarif);

    // Génération facture
    char filename[100];
    sprintf(filename,"facture_%d.txt", res.id);
    FILE* fp = fopen(filename,"w");
    if(fp){
        int duree = heureEnMinutes(res.heure_fin)-heureEnMinutes(res.heure_debut);
        fprintf(fp,"===== FACTURE =====\nID Reservation : %d\nClient : %s\nSalle : %s\nDate : %s\nHeure : %s - %s\nDuree : %d h %d min\nMontant : %.2f TND\n",
                res.id,res.nom_client,res.salle.nom,res.date,res.heure_debut,res.heure_fin,duree/60,duree%60,res.tarif);
        fclose(fp);
    }
    return 1;
}

// ============================
// Statistiques
// ============================
void statistiquesCompletes(){
    int dureeTotale[MAX_SALLES] = {0};
    float chiffreTotal[MAX_SALLES] = {0};

    // Calcul par salle
    for(int i=0;i<nb_reservations;i++){
        if(strcmp(reservations[i].statut,"confirmee")==0){
            for(int j=0;j<nb_salles;j++){
                if(strcmp(reservations[i].salle.nom,salles[j].nom)==0){
                    int duree = heureEnMinutes(reservations[i].heure_fin)-heureEnMinutes(reservations[i].heure_debut);
                    dureeTotale[j]+=duree;
                    chiffreTotal[j]+=reservations[i].tarif;
                }
            }
        }
    }

    // Affichage
    printf("\n=== STATISTIQUES ===\n");
    printf("\nChiffre d'affaires par salle :\n");
    for(int i=0;i<nb_salles;i++)
        printf("%s : %.2f TND\n", salles[i].nom, chiffreTotal[i]);

    printf("\nDurée totale par salle :\n");
    for(int i=0;i<nb_salles;i++)
        printf("%s : %d h %d min\n", salles[i].nom, dureeTotale[i]/60, dureeTotale[i]%60);

    printf("\n=== Reservations confirmees ===\n");
    for(int i=0;i<nb_reservations;i++){
        if(strcmp(reservations[i].statut,"confirmee")==0){
            printf("ID %d | %s | Salle : %s | Date : %s | %s-%s | %d personnes | %.2f TND\n",
                   reservations[i].id,reservations[i].nom_client,reservations[i].salle.nom,reservations[i].date,
                   reservations[i].heure_debut,reservations[i].heure_fin,reservations[i].nombre_personnes,reservations[i].tarif);
        }
    }
}

// ============================
// Recommandation de salle
// ============================
void recommanderSalles(int nb_personnes, char* date, char* debut, char* fin){
    printf("\n--- Salles disponibles pour %d personnes le %s de %s a %s ---\n", nb_personnes, date, debut, fin);
    int trouve = 0;
    for(int i=0;i<nb_salles;i++){
        if(salles[i].capacite>=nb_personnes && salleDisponible(salles[i],date,debut,fin)){
            printf("%s (Capacite: %d, Tarif: %.2f TND/h)\n", salles[i].nom,salles[i].capacite,salles[i].tarif_horaire);
            trouve = 1;
        }
    }
    if(!trouve) printf("Aucune salle disponible pour ce nombre de personnes et ce creneau.\n");
}

// ============================
// Annulation ou modification
// ============================
void annulerModifierReservation(){
    if(nb_reservations==0){ printf("Aucune reservation.\n"); return; }
    int id;
    printf("Entrez l'ID de la reservation : ");
    scanf("%d",&id);
    getchar();

    int trouve=0;
    for(int i=0;i<nb_reservations;i++){
        if(reservations[i].id==id && strcmp(reservations[i].statut,"confirmee")==0){
            trouve=1;
            printf("Reservation trouvee : ID %d | %s dans %s le %s de %s a %s\n",
                   reservations[i].id,reservations[i].nom_client,reservations[i].salle.nom,reservations[i].date,
                   reservations[i].heure_debut,reservations[i].heure_fin);
            printf("1) Annuler\n2) Modifier\nVotre choix : ");
            int choix;
            scanf("%d",&choix);
            getchar();
            if(choix==1){
                strcpy(reservations[i].statut,"annulee");
                printf("Reservation annulee.\n");
            } else if(choix==2){
                printf("Modification de la reservation.\n");
                char date[11],debut[6],fin[6];
                int nb_personnes;
                printf("Nombre de personnes : ");
                scanf("%d",&nb_personnes);
                getchar();
                lireDate(date);
                lireHeure(debut,"Heure debut");
                lireHeure(fin,"Heure fin");
                if(!salleDisponible(reservations[i].salle,date,debut,fin)){
                    printf("Salle non disponible a ce nouveau creneau.\n");
                } else {
                    reservations[i].nombre_personnes=nb_personnes;
                    strcpy(reservations[i].date,date);
                    strcpy(reservations[i].heure_debut,debut);
                    strcpy(reservations[i].heure_fin,fin);
                    reservations[i].tarif = calculTarif(reservations[i].salle,debut,fin);
                    printf("Reservation modifiee.\n");
                }
            } else printf("Choix invalide.\n");
            break;
        }
    }
    if(!trouve) printf("Reservation non trouvee.\n");
}

// ============================
// Menu principal
// ============================
void menu(){
    int choix;
    int nextId = nb_reservations+1;
    char buffer[50];

    do{
        printf("\n--- MENU ---\n");
        printf("1. Ajouter une reservation\n");
        printf("2. Afficher la liste des salles\n");
        printf("3. Afficher les statistiques\n");
        printf("4. Annuler ou modifier une reservation\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        fgets(buffer,sizeof(buffer),stdin);
        choix = atoi(buffer);

        if(choix==1){
            char nom_client[50], nom_salle[50], date[11], debut[6], fin[6];
            int nb_personnes;

            printf("Nom du client : ");
            fgets(nom_client,sizeof(nom_client),stdin);
            nom_client[strcspn(nom_client,"\n")]=0;

            printf("Nombre de personnes : ");
            fgets(buffer,sizeof(buffer),stdin);
            nb_personnes = atoi(buffer);

            lireDate(date);
            lireHeure(debut,"Heure debut");
            lireHeure(fin,"Heure fin");

            recommanderSalles(nb_personnes,date,debut,fin);

            printf("Voulez-vous : 1) Estimer le cout  2) Reserver directement ? ");
            int choix2;
            fgets(buffer,sizeof(buffer),stdin);
            choix2 = atoi(buffer);

            printf("Choisir la salle (nom) : ");
            fgets(nom_salle,sizeof(nom_salle),stdin);
            nom_salle[strcspn(nom_salle,"\n")]=0;

            if(choix2==1){
                Salle* salle=NULL;
                for(int i=0;i<nb_salles;i++){
                    if(strcmp(salles[i].nom,nom_salle)==0){ salle=&salles[i]; break;}
                }
                if(salle){
                    int minutes = heureEnMinutes(fin)-heureEnMinutes(debut);
                    float tarif = (minutes/60.0)*salle->tarif_horaire;
                    printf("Estimation : %s | Date : %s | Heure : %s-%s | Nombre : %d\nDuree : %d h %d min | Cout estime : %.2f TND\n",
                           salle->nom,date,debut,fin,nb_personnes,minutes/60,minutes%60,tarif);
                }
            } else if(choix2==2){
                ajouterReservation(nextId++,nom_client,nom_salle,date,debut,fin,nb_personnes);
            } else printf("Choix invalide.\n");

        } else if(choix==2) afficherSalles();
        else if(choix==3) statistiquesCompletes();
        else if(choix==4) annulerModifierReservation();
        else if(choix==5) printf("Au revoir !\n");
        else printf("Choix invalide.\n");

    }while(choix!=5);
}

// ============================
// Programme principal
// ============================
int main(){
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    setlocale(LC_ALL,"");

    // Ajouter salles
    ajouterSalle("Mercure",30,10.0,"Wi-Fi");
    ajouterSalle("Venus",30,18.0,"Projecteur, Wi-Fi");
    ajouterSalle("Terre",20,25.0,"Projecteur, Wi-Fi, Tableau blanc");
    ajouterSalle("Mars",19,15.0,"Wi-Fi, Tableau blanc");
    ajouterSalle("Jupiter",30,30.0,"Projecteur, Wi-Fi, Tableau blanc");
    ajouterSalle("Saturne",40,20.0,"Wi-Fi, Tableau blanc");
    ajouterSalle("Uranus",50,12.0,"Wi-Fi");
    ajouterSalle("Neptune",45,15.0,"Projecteur");

    // Ajouter reservations initiales
    ajouterReservation(1,"Entreprise SAHARA TECH","Terre","10/12/2025","09:00","11:00",15);
    ajouterReservation(2,"Startup El Medina","Venus","10/12/2025","10:00","12:00",12);
    ajouterReservation(3,"Association Jeunesse Tunisienne","Mars","11/12/2025","14:00","15:30",8);

    menu();
    return 0;
}
