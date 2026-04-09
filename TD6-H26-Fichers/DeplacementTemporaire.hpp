/**
 * \file DeplacementTemporaire.hpp
 * \brief Classe RAII pour deplacer temporairement une piece.
 */

#pragma once

#include "Piece.hpp"

namespace modele {

class DeplacementTemporaire
{
public:
	DeplacementTemporaire(Piece& piece, const Position& nouvellePosition);
	~DeplacementTemporaire();

	DeplacementTemporaire(const DeplacementTemporaire&) = delete;
	DeplacementTemporaire& operator=(const DeplacementTemporaire&) = delete;

	// TODO(Personne 2) :
	// 1. Garder l'interdiction de copie pour eviter deux restaurations.
	// 2. Decider si vous voulez aussi interdire le deplacement de cet objet.
	// 3. Au besoin, ajouter une methode pour lire l'ancienne position.
	// 4. Ne pas faire dependre cette classe de l'affichage.

private:
	Piece& piece_;
	Position anciennePosition_{};
};

}  // namespace modele
