#include "DeplacementTemporaire.hpp"

#include <utility>

namespace modele {

	DeplacementTemporaire::DeplacementTemporaire(Echiquier& echiquier,
		const Position& depart,
		const Position& arrivee)
		: echiquier_(echiquier)
		, depart_(depart)
		, arrivee_(arrivee)
	{
		std::unique_ptr<Piece> pieceMobile =
			echiquier_.retirerPiece(depart_);
		if (pieceMobile == nullptr) {
			return;
		}

		pieceCapturee_ = echiquier_.retirerPiece(arrivee_);

		pieceMobile->deplacer(arrivee_);
		echiquier_.placerPiece(std::move(pieceMobile));

		deplacementEffectue_ = true;
	}

	DeplacementTemporaire::~DeplacementTemporaire()
	{
		if (!deplacementEffectue_) {
			return;
		}

		std::unique_ptr<Piece> pieceMobile =
			echiquier_.retirerPiece(arrivee_);
		if (pieceMobile != nullptr) {
			pieceMobile->deplacer(depart_);
			echiquier_.placerPiece(std::move(pieceMobile));
		}

		if (pieceCapturee_ != nullptr) {
			echiquier_.placerPiece(std::move(pieceCapturee_));
		}
	}

}