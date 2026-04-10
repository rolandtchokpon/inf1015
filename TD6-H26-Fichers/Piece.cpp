/**
 * \file Piece.cpp
 * \brief Implementation de la classe Piece.
 */

#include "Piece.hpp"

namespace modele {

Piece::Piece(const Position& positionInitiale)
	: position_(positionInitiale)
{
}

const Position& Piece::obtenirPosition() const
{
	return position_;
}

void Piece::deplacer(const Position& nouvellePosition)
{
	position_ = nouvellePosition;
}

}  // namespace modele
