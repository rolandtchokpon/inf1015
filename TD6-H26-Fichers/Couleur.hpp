/**
 * Enumeration des couleurs des pieces.
 * \file   Couleur.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 25 avril 2026
 */

#pragma once

namespace modele {

	enum class Couleur
	{
		blanc,
		noir
	};

	inline Couleur couleurOpposee(Couleur couleur)
	{
		if (couleur == Couleur::blanc) {
			return Couleur::noir;
		}
		return Couleur::blanc;
	}

}  