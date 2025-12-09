#include "gestion.h"
#include <locale.h>

int main(){
    setlocale(LC_ALL, "");

    ajouterSalle("Mercure", 30, 10.0, "Wi-Fi");
    ajouterSalle("Venus", 30, 18.0, "Projecteur, Wi-Fi");

    ajouterReservation(1, "Entreprise A", "Mercure", "10/12/2025", "09:00", "11:00", 15);

    menu();

    return 0;
}
