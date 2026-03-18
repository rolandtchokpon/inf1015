// Fichier: Affichable.hpp
// Auteurs:
// Description: Interface commune des objets pouvant s'afficher et changer de couleur.

#pragma once
#include <string>
#include <iostream>

using namespace std;

// Interface commune pour tous les objets pouvant s'afficher sur un flux
// et adapter leur couleur selon une palette logique.
class Affichable {
	public:
		virtual ~Affichable() = default;
		virtual void afficher(ostream& os) const = 0;
		virtual void changerCouleur(const string& palette) = 0;
};
