# 🏢 Gestion des Salles & Réservations – Projet en C

![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)

Ce projet consiste à développer une application en *C* permettant de gérer des salles, leurs réservations, les conflits horaires, l’estimation des coûts, et la persistance des données via des fichiers.

---

## 📑 Sommaire
1. [Fonctionnalités](#-fonctionnalités)
2. [Structure du Projet](#-structure-du-projet)
3. [Compilation](#️-compilation)

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
  - - nombre de personnes
  - date  
  - heure début
  - heure fin 
  - salle choisie  
    
- Détection des *conflits de créneaux*
- Modification et suppression de réservation
- Estimation *automatique du coût* de réservation

### 🔄 Sauvegarde des données
- Sauvegarde et lecture depuis fichiers texte/binaire :
  - reservations.txt
  - tarif.txt

---

## 📂 Structure du Projet



Projet/
│── main.c
│── salle.c
│── salle.h
│── reservation.c
│── reservation.h
│── fonctionsAux.c
│── fonctionsAux.h
│── data/
│ ├── salles.txt
│ ├── reservations.txt
│── README.md
