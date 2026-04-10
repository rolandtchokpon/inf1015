/**
 * \file Piece.hpp
 * \brief Declaration de la classe de base Piece.
 */

#pragma once
#include "Position.hpp"

namespace modele {

class Piece
{
public:
	Piece() = default;
	explicit Piece(const Position& positionInitiale);
	virtual ~Piece() = default;

	// Retourne la position actuelle de la piece.
	const Position& obtenirPosition() const;

	// Deplace la piece a une nouvelle position.
	void deplacer(const Position& nouvellePosition);


private:
	// Chaque piece connait sa position sur l'echiquier.
	Position position_{};

};

}  // namespace modele
