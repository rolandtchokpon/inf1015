/**
 * \file Roi.hpp
 * \brief Declaration de la classe Roi.
 */

#pragma once

#include "ExceptionRoi.hpp"
#include "Piece.hpp"

namespace modele {

class Roi : public Piece
{
public:
	explicit Roi(const Position& positionInitiale);
	~Roi() override;

	// On interdit la copie pour ne pas fausser le compteur d'instances.
	Roi(const Roi&) = delete;
	Roi& operator=(const Roi&) = delete; 

	static int obtenirNombreInstances();

private:
	// Variable de classe partagee par tous les objets Roi.
	static int nombreInstances_;
};

}  // namespace modele
