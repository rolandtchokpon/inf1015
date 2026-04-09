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

	const Position& obtenirPosition() const;
	void deplacer(const Position& nouvellePosition);

	// TODO(Personne 1) :
	// 1. Ajouter les attributs communs a toutes les pieces.
	//    Exemples : couleur, nom, symbole.
	// 2. Ajouter les getters/setters necessaires pour ces attributs.
	// 3. Decider si Piece doit etre abstraite.
	//    Si oui, ajouter au moins une methode virtuelle pure.
	// 4. Verifier que cette classe ne depend pas de la vue.
	// 5. Ne pas utiliser using namespace dans ce fichier.

private:
	Position position_{};
};

}  // namespace modele
