/**
 * \file Roi.cpp
 * \brief Implementation de la classe Roi.
 */

#include "Roi.hpp"

namespace modele {

int Roi::nombreInstances_ = 0;

Roi::Roi(const Position& positionInitiale)
	: Piece(positionInitiale)
{
	// Chaque construction ajoute un roi vivant au compteur.
	++nombreInstances_;
	if (nombreInstances_ > 2) {
		--nombreInstances_;
		throw ExceptionRoi();
	}
}

Roi::~Roi()
{
	// Quand un roi est detruit, son instance est retiree du compteur.
	if (nombreInstances_ > 0) {
		--nombreInstances_;
	}
}

int Roi::obtenirNombreInstances()
{
	return nombreInstances_;
}


}  // namespace modele
