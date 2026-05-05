/**
 * Classe Roi : piece avec compteur d'instances limite a deux.
 * \file   Roi.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#pragma once

#include "Couleur.hpp"
#include "ExceptionRoi.hpp"
#include "Piece.hpp"

namespace modele {

	class Roi : public Piece
	{
	public:
		Roi(const Position& positionInitiale, Couleur couleur);
		~Roi() override;

		Roi(const Roi&) = delete;
		Roi& operator=(const Roi&) = delete;

		bool estMouvementValide(
			const Position& destination) const override;
		char obtenirSymbole() const override;

		static int obtenirNombreInstances();

	private:
		static int nombreInstances_;
	};

}  