// main.cpp
#include <iostream>
#include "Modele.h"

int main() {
    Modele* modele = new Modele(2); // Crée un modèle avec 2 joueurs
    std::cout << "Modèle créé avec succès." << std::endl;
    delete modele; // Libérer la mémoire
    return 0;
}

