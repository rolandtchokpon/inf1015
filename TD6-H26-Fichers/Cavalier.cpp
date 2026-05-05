/**
 * Implementation de la classe Cavalier.
 * \file   Cavalier.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include "Cavalier.hpp"

#include <cstdlib>

namespace modele {

	Cavalier::Cavalier(const Position& positionInitiale, Couleur couleur)
		: Piece(positionInitiale, couleur)
	{
	}


	bool Cavalier::estMouvementValide(const Position& destination) const
	{
		const Position& depart = obtenirPosition();
		int differenceLigne = std::abs(destination.ligne - depart.ligne);
		int differenceColonne = std::abs(destination.colonne - depart.colonne);

		bool formeLongueLigne = differenceLigne == 2 && differenceColonne == 1;
		bool formeLongueColonne = differenceLigne == 1 && differenceColonne == 2;
		return formeLongueLigne || formeLongueColonne;
	}


	char Cavalier::obtenirSymbole() const
	{
		return 'C';
	}


	bool Cavalier::peutSauterPieces() const
	{
		return true;
	}

}  