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
	// Le message sera recupere plus tard avec what().
	ExceptionRoi()
		: std::runtime_error("Impossible de creer plus de deux rois.")
	{
	}

};

}  // namespace modele
