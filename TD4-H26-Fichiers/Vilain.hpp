#pragma once
#include <iostream>
#include <string>
#include "Personnage.hpp"

using namespace std;

// Specialisation de Personnage representant un antagoniste.
// Le vilain ajoute un objectif a l'identite de base du personnage.
class Vilain : public virtual Personnage
{
public:
	Vilain(const string& nom, const string& parution, const string& objectif)
		: Personnage(nom, parution), objectif_(objectif)
	{
	}

	void afficher(ostream& os) const override;

	const string& getObjectif() const;


private:
	string objectif_;
};

// Accesseur utilise pour fusionner un vilain avec un heros.
const string& Vilain::getObjectif() const {
	return objectif_;
}

// Complete l'affichage de base avec l'objectif du vilain.
void Vilain::afficher(ostream& os) const {
	Personnage::afficher(os);
	os << "Objectif : " << objectif_ << "\n";
}
