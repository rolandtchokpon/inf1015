/**
 * \file Affichage.cpp
 * \brief Implementation des fonctions d'affichage.
 */

#include "Affichage.hpp"

#include <iostream>

namespace vue {

void afficherMessageErreur(const std::string& message)
{
	// TODO(Personne 2) :
	// 1. Remplacer std::cout par QMessageBox ou autre si votre projet a une vue Qt.
	// 2. Garder ici seulement l'affichage du message, pas la logique du modele.
	std::cout << "Erreur : " << message << std::endl;
}

void afficherPositionPiece(const modele::Piece& piece)
{
	// TODO(Personne 2) :
	// 1. Adapter cet affichage a votre vraie representation d'une piece.
	// 2. Ajouter au besoin la couleur, le nom ou le type de la piece.
	const modele::Position& position = piece.obtenirPosition();
	std::cout
		<< "Position de la piece : ("
		<< position.ligne
		<< ", "
		<< position.colonne
		<< ")"
		<< std::endl;
}

}  // namespace vue
