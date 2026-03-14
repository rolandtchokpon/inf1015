#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Personnage.hpp"


class Heros : public virtual Personnage
{
public:
	Heros(const string& nom, const string& parution, const string& ennemi, const vector<string>& allies)
		: Personnage(nom, parution), ennemi_(ennemi), allies_(allies)
	{
	}
	void afficher(ostream& os) const override;
	const string& getEnnemi() const;
	const vector<string>& getAllies() const;


private: 
	string ennemi_;
	vector<string> allies_;

};

const string& Heros::getEnnemi() const {
	return ennemi_;
}

const vector<string>& Heros::getAllies() const {
		return allies_;
}

void Heros::afficher(ostream& os) const 
{
	Personnage::afficher(os);
	os << "Ennemi : " << ennemi_ << "\n";
	os << "Allies : \n"; 
	for (const string& allie : allies_) {
		os << allie << "\n";
	}
}	