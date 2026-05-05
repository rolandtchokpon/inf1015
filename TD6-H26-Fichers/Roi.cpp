/**
 * Implementation de la classe Roi.
 * \file   Roi.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include "Roi.hpp"

#include <cstdlib>

namespace modele {

	int Roi::nombreInstances_ = 0;

	namespace {
		constexpr int nombreRoisMaximum = 2;
	}  // namespace anonyme


	Roi::Roi(const Position& positionInitiale, Couleur couleur)
		: Piece(positionInitiale, couleur)
	{
		++nombreInstances_;
		if (nombreInstances_ > nombreRoisMaximum) {
			--nombreInstances_;
			throw ExceptionRoi();
		}
	}


	Roi::~Roi()
	{
		if (nombreInstances_ > 0) {
			--nombreInstances_;
		}
	}


	bool Roi::estMouvementValide(const Position& destination) const
	{
		const Position& depart = obtenirPosition();
		if (destination == depart) {
			return false;
		}
		int differenceLigne = std::abs(destination.ligne - depart.ligne);
		int differenceColonne = std::abs(destination.colonne - depart.colonne);

		return differenceLigne <= 1 && differenceColonne <= 1;
	}


	char Roi::obtenirSymbole() const
	{
		return 'R';
	}


	int Roi::obtenirNombreInstances()
	{
		return nombreInstances_;
	}

}  