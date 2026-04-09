/**
 * \file Position.hpp
 * \brief Type simple pour representer une position sur l'echiquier.
 */

#pragma once

namespace modele {

struct Position
{
	int ligne = 0;
	int colonne = 0;

	// TODO(Personne 1) :
	// 1. Decider si vous gardez ligne/colonne ou si vous renommez en x/y.
	// 2. Choisir la convention des valeurs valides, par exemple 0 a 7.
	// 3. Ajouter au besoin un constructeur Position(int, int).
	// 4. Ajouter au besoin operator== pour comparer deux positions.
};

}  // namespace modele
