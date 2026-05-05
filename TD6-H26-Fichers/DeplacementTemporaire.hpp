#pragma once

#include <memory>

#include "Echiquier.hpp"
#include "Piece.hpp"
#include "Position.hpp"

namespace modele {

	class DeplacementTemporaire
	{
	public:
		DeplacementTemporaire(Echiquier& echiquier,
			const Position& depart,
			const Position& arrivee);
		~DeplacementTemporaire();

		DeplacementTemporaire(
			const DeplacementTemporaire&) = delete;
		DeplacementTemporaire& operator=(
			const DeplacementTemporaire&) = delete;

	private:
		Echiquier& echiquier_;
		Position               depart_{};
		Position               arrivee_{};
		std::unique_ptr<Piece> pieceCapturee_{};
		bool                   deplacementEffectue_ = false;
	};

}