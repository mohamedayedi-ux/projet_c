#include <locale.h>
#include "salles.h"
#include "reservations.h"
#include "interface.h"

int main(){

    setlocale(LC_ALL, "");

    ajouterSalle("Mercure", 30, 10.0, "Wi-Fi");
    ajouterSalle("Venus", 30, 18.0, "Projecteur, Wi-Fi");
    ajouterSalle("Terre", 20, 25.0, "Projecteur, Wi-Fi, Tableau blanc");

    ajouterReservation(1,"Entreprise A","Terre","10/12/2025","09:00","11:00",15);

    menu();
    return 0;
}
