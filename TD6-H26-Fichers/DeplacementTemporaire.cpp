/**
 * \file DeplacementTemporaire.cpp
 * \brief Implementation de la classe RAII DeplacementTemporaire.
 */

#include "DeplacementTemporaire.hpp"

namespace modele {

DeplacementTemporaire::DeplacementTemporaire(
	Piece& piece,
	const Position& nouvellePosition)
	: piece_(piece),
	  anciennePosition_(piece.obtenirPosition())
{
	// TODO(Personne 2) :
	// 1. Verifier que la piece recue en parametre existe pendant toute
	//    la duree de vie de cet objet RAII.
	// 2. Ajouter une validation de position si votre projet en a besoin.
	piece_.deplacer(nouvellePosition);
}

DeplacementTemporaire::~DeplacementTemporaire()
{
	// TODO(Personne 2) :
	// 1. Garder ici le retour automatique a l'ancienne position.
	// 2. Tester avec un bloc local pour verifier que la restauration
	//    se fait bien a la destruction.
	piece_.deplacer(anciennePosition_);
}

}  // namespace modele
