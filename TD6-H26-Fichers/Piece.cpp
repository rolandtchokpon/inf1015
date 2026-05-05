/**
 * Implementation de la classe de base Piece.
 * \file   Piece.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include "Piece.hpp"

namespace modele {

	Piece::Piece(const Position& positionInitiale, Couleur couleur)
		: position_(positionInitiale)
		, couleur_(couleur)
	{
	}


	const Position& Piece::obtenirPosition() const
	{
		return position_;
	}


	Couleur Piece::obtenirCouleur() const
	{
		return couleur_;
	}


	void Piece::deplacer(const Position& nouvellePosition)
	{
		position_ = nouvellePosition;
	}


	bool Piece::peutSauterPieces() const
	{
		return false;
	}

}  