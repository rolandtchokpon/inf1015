#pragma once
#include <iostream>
#include <string>
#include "Personnage.hpp"

using namespace std;

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

const string& Vilain::getObjectif() const {
	return objectif_;
}

void Vilain::afficher(ostream& os) const {
	Personnage::afficher(os);
	os << "Objectif : " << objectif_ << "\n";
}