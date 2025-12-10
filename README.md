# 🏢 Gestion des Salles & Réservations – Projet en C

![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)

Ce projet consiste à développer une application en *C* permettant de gérer des *salles*, leurs *réservations*, les *conflits horaires*, l’**estimation des coûts**, et la *persistance des données* via des fichiers.

---

## 📑 Sommaire
1. [Fonctionnalités](#-fonctionnalités)
2. [Structure du Projet](#-structure-du-projet)
3. [Compilation](#-compilation)
4. [Exécution](#-exécution)
5. [Détails Techniques](#-détails-techniques)
6. [Auteurs](#-auteurs)
---

## 🚀 Fonctionnalités

### 🏢 Gestion des salles
- Ajouter une salle (nom, capacité, tarif horaire, équipements)
- Modifier ou supprimer une salle
- Lister toutes les salles
- Recommandation automatique selon la capacité

### 📅 Gestion des réservations
- Ajouter une réservation avec :
  - nom du client
  - nombre de personnes
  - date  
  - heure début
  - heure fin 
  - salle choisie  
    
- Détection des *conflits de créneaux*
- Modification et suppression de réservation
- *Estimation automatique du coût* de réservation

### 🔄 Sauvegarde des données
- Sauvegarde et lecture depuis fichiers texte/binaire :
  - Reservations.txt
  - Tarif.txt
  - Facture_(id_facture).txt

---

## 📂 Structure du Projet



Projet/
│── Main.c
│── Menu.c
│── Menu.h
│── GestionSalle.c
│── GestionSalle.h
│── Reservation.c
│── Reservation.h
│── FonctionsAux.c
│── FonctionsAux.h
│── Facture.c
│── Facture.h
│── Structures.c
│── Structures.h
│── Stats.c
│── Stats.h
│── data/
│ ├── Tarif.txt
│ ├── Reservations.txt
│ ├── Facture_(nom facture).txt
│── README.md

---

## 🖥️⚙️ Compilation

 GCC.txt

 ---

## ▶️ Exécution

 Systeme_de_Gestion_de_Reservations.exe

 ---

## 🔍 Détails techniques

⚙️ Détails Techniques

1. 🧱 Organisation des Données avec les struct C

Les structures fondamentales définies dans Structures.h :

- **Salle**
Contient : nom, capacité, tarif horaire, équipements.
- **Reservation**
Contient : ID, nom client, salle (par valeur), date, heures début/fin, nombre de personnes, tarif, statut.

Les structures sont stockées dans des tableaux globaux définis dans main.c, avec limites fixées par :
MAX_SALLES et MAX_RES (Structures.h).

2. 🏢 Gestion des Salles & Persistance

- Les salles initiales sont créées dans main() via ajouterSalle().
- Le fichier Tarif.txt assure la persistance, généré par creerFichierTarif() (GestionSalle.c).
- La recherche d’une salle se fait avec trouverSalle().

3. ⏱️ Détection des Conflits Horaires

Gestion réalisée en trois étapes :

 a) Conversion en minutes:
heureEnMinutes() convertit "HH:MM" → minutes depuis minuit.
 b) Vérification de chevauchement:
chevauche(debut1, fin1, debut2, fin2) retourne 1 si :
      (d1​<f2​)∧(d2​<f1​)     
 c) Disponibilité finale
salleDisponible() utilise chevauche() pour s’assurer qu’aucune réservation "confirmee" ou "modifiee" ne bloque l’horaire.

4. 💰 Calcul du Tarif

Effectué par calculTarif() (FonctionsAux.c).

Formule utilisée :
   Tarif Total=-(Heure_Fin−Heure_Debut​)/60)×Tarif_Horaire

Contraintes horaires :
- début ≥ 08:00 (480 min)
- fin ≤ 23:59 (1439 min)
- fin > début

5. 📊 Statistiques & Rapports

Module : Stats.c

- Chiffre d’affaires par salle basé sur les réservations confirmées.
- Réservations par mois : compterReservationsParMois(mois, annee)
- Salles les plus populaires : afficherSallesPopulaires(mois, annee)

 ---


## 💡 Auteurs

- Yasmine TRIKI
- Mohamed AYEDI
- Mohamed Louai DARGUECH
