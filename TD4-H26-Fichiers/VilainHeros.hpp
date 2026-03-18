// Fichier: VilainHeros.hpp
// Auteurs:
// Description: Definition de la classe issue de l'heritage multiple VilainHeros.

#pragma once 
#include <ostream>
#include <string>
#include "Vilain.hpp"
#include "Heros.hpp"

// Fusion d'un vilain et d'un heros.
// Cette classe combine les attributs herites des deux branches et ajoute
// une mission speciale derivee du contexte du heros.
class VilainHeros : public Vilain, public Heros
{
public:
	VilainHeros(const Vilain& vilain, const Heros& heros)
		: Personnage(
			vilain.getNom() + "-" + heros.getNom(),
			vilain.getParution() + "-" + heros.getParution()
		),
		Vilain(
			vilain.getNom() + "-" + heros.getNom(),
			vilain.getParution() + "-" + heros.getParution(),
			vilain.getObjectif()
		),
		Heros(
			vilain.getNom() + "-" + heros.getNom(),
			vilain.getParution() + "-" + heros.getParution(),
			heros.getEnnemi(), heros.getAllies()
		),
		missionSpeciale_(vilain.getObjectif() + " dans le monde de " + heros.getParution())
	{
	}

	void afficher(ostream& os) const override;

private:
	string missionSpeciale_;
};

// Assemble manuellement l'affichage pour eviter de dupliquer la partie
// Personnage via Heros::afficher et Vilain::afficher.
void VilainHeros::afficher(ostream& os) const {
	Personnage::afficher(os);
	
	os << "Objectif : " << getObjectif() << "\n"
	   << "Ennemi : " << getEnnemi() << "\n"
	   << "Allies :\n";
	   for (const string& allie : getAllies()) {
		  os << allie << "\n";
	   }
	os << "Mission speciale : " << missionSpeciale_ << "\n";
}
