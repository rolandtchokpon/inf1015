/**
 * Classe Tour : piece se deplacant en ligne droite.
 * \file   Tour.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#pragma once

#include "Couleur.hpp"
#include "Piece.hpp"

namespace modele {

	class Tour : public Piece
	{
	public:
		Tour(const Position& positionInitiale, Couleur couleur);
		~Tour() override = default;

		bool estMouvementValide(
			const Position& destination) const override;
		char obtenirSymbole() const override;
	};

}  