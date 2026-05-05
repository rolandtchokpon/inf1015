/**
 * Classe de base abstraite pour toutes les pieces du jeu d'echecs.
 * \file   Piece.hpp
 * \author [Vos noms]
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#pragma once

#include "Couleur.hpp"
#include "Position.hpp"

namespace modele {

	class Piece
	{
	public:
		Piece() = default;
		Piece(const Position& positionInitiale, Couleur couleur);
		virtual ~Piece() = default;

		const Position& obtenirPosition() const;
		Couleur         obtenirCouleur()  const;

		void deplacer(const Position& nouvellePosition);

		virtual bool estMouvementValide(
			const Position& destination) const = 0;

		virtual char obtenirSymbole() const = 0;

		virtual bool peutSauterPieces() const;

	private:
		Position position_{};
		Couleur  couleur_ = Couleur::blanc;
	};

}  // namespace modele