/**
 * Classe Echiquier : grille 8x8 proprietaire des pieces.
 * \file   Echiquier.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#pragma once

#include <array>
#include <memory>

#include "Couleur.hpp"
#include "Piece.hpp"
#include "Position.hpp"

namespace modele {

	constexpr int tailleEchiquier = 8;

	class Echiquier
	{
	public:
		Echiquier() = default;

		Echiquier(const Echiquier&) = delete;
		Echiquier& operator=(const Echiquier&) = delete;

		Piece* obtenirPiece(const Position& position) const;

		std::unique_ptr<Piece> placerPiece(std::unique_ptr<Piece> piece);

		std::unique_ptr<Piece> retirerPiece(const Position& position);

		
		bool deplacerPiece(const Position& depart,
			const Position& arrivee);

		
		bool estEnEchec(Couleur couleur) const;

		
		Position trouverPositionRoi(Couleur couleur) const;

		static bool estDansLimites(const Position& position);

		void vider();

	private:
		bool cheminEstLibre(const Position& depart,
			const Position& arrivee) const;

		
		bool peutAtteindre(const Position& depart,
			const Position& arrivee) const;

		std::array<std::array<std::unique_ptr<Piece>, tailleEchiquier>,
			tailleEchiquier> cases_{};
	};

}  