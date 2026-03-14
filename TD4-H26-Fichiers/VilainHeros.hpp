#pragma once 
#include <ostream>
#include <string>
#include "Vilain.hpp"
#include "Heros.hpp"

class VilainHeros : public Vilain, public Heros
{
public:
	VilainHeros(const Vilain& vilain, const Heros& heros, const string& missionSpeciale)
		: Personnage(
					vilain.getNom() + "-" + heros.getNom(),
					vilain.getParution() + "-" + heros.getParution()
					),
		  Vilain(vilain.getObjectif()),
		  Heros(
					vilain.getEnnemi(), parution, ennemi, allies),
		          
		          missionSpeciale_(missionSpeciale)
	{
	}

	void afficher(ostream& os) const;

private:
	string missionSpeciale_;
};

void VilainHeros::afficher(ostream& os) const {
	Personnage::afficher(os);

	os << "Objectif" << vilain.getObjectif()
}