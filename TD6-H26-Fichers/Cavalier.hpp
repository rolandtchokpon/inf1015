/**
 * Classe Cavalier : piece se deplacant en L et pouvant sauter.
 * \file   Cavalier.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#pragma once

#include "Couleur.hpp"
#include "Piece.hpp"

namespace modele {

	class Cavalier : public Piece
	{
	public:
		Cavalier(const Position& positionInitiale, Couleur couleur);
		~Cavalier() override = default;

		bool estMouvementValide(
			const Position& destination) const override;
		char obtenirSymbole() const override;

		bool peutSauterPieces() const override;
	};

}  