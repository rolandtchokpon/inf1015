#pragma once
#include <string>
#include <iostream>
#include "Affichable.hpp"

using namespace std;


class Personnage : public Affichable

{
public:
	Personnage(const string& nom, const string& parution):
		nom_(nom), parution_(parution), couleur_("heros")
	{}

	void afficher(ostream& os) const override;
	void changerCouleur(const string& palette) override;

	const string& getNom() const;
	const string& getParution() const;

protected:
	Personnage(const Personnage& autre) = default;
	Personnage& operator = (const Personnage& autre) = default;

private:
	string nom_;
	string parution_;
	string couleur_;
};

void Personnage::afficher(ostream& os) const {
	  os << couleur_ 
		 << "Nom : " << nom_ << "\n"
		 << "Parution : " << parution_ << "\n"
		 << "\033[0m";
}

const string& Personnage::getNom() const {
	return nom_;
}
const string& Personnage::getParution() const{
	return parution_;
}

void Personnage::changerCouleur(const string& palette) {
	if (palette == "heros") {
		couleur_ = "\033[94m";
	}
	else if (palette == "vilain") {
		couleur_ = "\033[91m";
	}
	else if (palette == "vilainHeros") {
		couleur_ = "\033[95m";
	}
	else {
		couleur_ = "\033[0m";
	}
}