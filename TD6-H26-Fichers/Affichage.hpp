/**
 * \file Affichage.hpp
 * \brief Fonctions d'affichage du projet.
 */

#pragma once

#include <string>

#include "Piece.hpp"

namespace vue {

void afficherMessageErreur(const std::string& message);
void afficherPositionPiece(const modele::Piece& piece);

// TODO(Personne 2) :
// 1. Decider si vous gardez un affichage console ou si vous passez a Qt.
// 2. Si vous utilisez Qt, remplacer ces fonctions par des fonctions
//    adaptees a votre interface.
// 3. Garder ce fichier dans le namespace vue uniquement.

}  // namespace vue
