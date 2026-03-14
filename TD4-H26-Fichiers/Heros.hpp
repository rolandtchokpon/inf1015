#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Personnage.hpp"


// Specialisation de Personnage representant un heros.
// Un heros connait son ennemi principal et la liste de ses allies.
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

// Accesseur utilise lors de la construction d'un VilainHeros.
const string& Heros::getEnnemi() const {
	return ennemi_;
}

// Accesseur utilise lors de la construction et de l'affichage d'un VilainHeros.
const vector<string>& Heros::getAllies() const {
		return allies_;
}

// Complete l'affichage de base avec les informations propres au heros.
void Heros::afficher(ostream& os) const 
{
	Personnage::afficher(os);
	os << "Ennemi : " << ennemi_ << "\n";
	os << "Allies : \n"; 
	for (const string& allie : allies_) {
		os << allie << "\n";
	}
}	
