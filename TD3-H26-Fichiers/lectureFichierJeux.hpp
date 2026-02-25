// Fonctions pour lire le fichier binaire.
#pragma once
#include "Jeu.hpp"
#include "Concepteur.hpp"
#include <iostream>
#include <memory>

std::shared_ptr<Concepteur> chercherConcepteur(ListeJeux& listeJeux, const std::string& nom);
std::shared_ptr<Concepteur> lireConcepteur(ListeJeux& lj, std::istream& f);
Jeu* lireJeu(std::istream& f, ListeJeux& lj);
ListeJeux creerListeJeux(const std::string& nomFichier);
