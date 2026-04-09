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
	Roi();
	explicit Roi(const Position& positionInitiale);
	~Roi() override;

	// TODO(Personne 1) :
	// 1. Decider si un Roi peut etre copie.
	// 2. Si la copie est interdite, supprimer le constructeur de copie
	//    et l'operateur=.
	// 3. Si la copie est permise, implementer la copie correctement
	//    pour maintenir le compteur d'instances.
	// 4. Verifier qu'on ne peut jamais avoir plus de 2 objets Roi vivants.

	static int obtenirNombreInstances();

private:
	static int nombreInstances_;
};

}  // namespace modele
