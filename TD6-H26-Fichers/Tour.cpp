/**
 * Implementation de la classe Tour.
 * \file   Tour.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include "Tour.hpp"

namespace modele {

	Tour::Tour(const Position& positionInitiale, Couleur couleur)
		: Piece(positionInitiale, couleur)
	{
	}


	bool Tour::estMouvementValide(const Position& destination) const
	{
		const Position& depart = obtenirPosition();
		if (destination == depart) {
			return false;
		}
		bool surMemeLigne = destination.ligne == depart.ligne;
		bool surMemeColonne = destination.colonne == depart.colonne;
		return surMemeLigne || surMemeColonne;
	}


	char Tour::obtenirSymbole() const
	{
		return 'T';
	}

}  