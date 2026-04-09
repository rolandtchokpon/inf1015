/**
 * \file Roi.cpp
 * \brief Implementation de la classe Roi.
 */

#include "Roi.hpp"

namespace modele {

int Roi::nombreInstances_ = 0;

Roi::Roi()
{
	// TODO(Personne 1) :
	// 1. Verifier que ce constructeur convient a votre projet.
	// 2. Si un Roi doit toujours avoir une position valide, vous pouvez
	//    supprimer ce constructeur par defaut.
	++nombreInstances_;
	if (nombreInstances_ > 2) {
		--nombreInstances_;
		throw ExceptionRoi();
	}
}

Roi::Roi(const Position& positionInitiale)
	: Piece(positionInitiale)
{
	// TODO(Personne 1) :
	// 1. Garder cette logique si le compteur doit etre incremente ici.
	// 2. Si vous ajoutez un constructeur de copie, reutiliser la meme regle.
	++nombreInstances_;
	if (nombreInstances_ > 2) {
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

int Roi::obtenirNombreInstances()
{
	return nombreInstances_;
}

// TODO(Personne 1) :
// 1. Tester les cas suivants :
//    - creation du 1er roi
//    - creation du 2e roi
//    - tentative de creation du 3e roi
//    - destruction d'un roi puis recreation d'un autre
// 2. Verifier que le compteur revient a 0 a la fin du programme.

}  // namespace modele
