/**
 * \file Position.hpp
 * \brief Type simple pour representer une position sur l'echiquier.
 */

#pragma once

namespace modele {
	// Convention retenue : sur un echiquier 8x8,
	// ligne et colonne prennent des valeurs entre 0 et 7.
	struct Position
	{
		int ligne = 0;
		int colonne = 0;

		
		Position() = default;
		Position(int ligne, int colonne) :
			ligne(ligne), colonne(colonne)
		{
		}

		bool operator==(const Position& pos) const {
			return ligne == pos.ligne && colonne == pos.colonne;
		}
	};

}  // namespace modele
