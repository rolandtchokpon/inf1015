/**
 * \file ExceptionRoi.hpp
 * \brief Exception lancee lorsqu'il y a plus de deux rois.
 */

#pragma once

#include <stdexcept>

namespace modele {

class ExceptionRoi : public std::runtime_error
{
public:
	ExceptionRoi()
		: std::runtime_error("Impossible de creer plus de deux rois.")
	{
	}

	// TODO(Personne 1) :
	// 1. Decider si ce message est suffisant pour votre remise.
	// 2. Si non, remplacer le texte par un message plus precis.
	// 3. Garder un nom de classe conforme au guide : suffixe Exception
	//    ou prefixe Exception.
};

}  // namespace modele
