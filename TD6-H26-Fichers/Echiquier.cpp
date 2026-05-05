/**
 * Implementation de la classe Echiquier.
 * \file   Echiquier.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include "Echiquier.hpp"

#include <utility>

#include "DeplacementTemporaire.hpp"
#include "Roi.hpp"

namespace modele {

	namespace {
		constexpr int positionInvalide = -1;
	}  


	Piece* Echiquier::obtenirPiece(const Position& position) const
	{
		if (!estDansLimites(position)) {
			return nullptr;
		}
		return cases_[position.ligne][position.colonne].get();
	}


	std::unique_ptr<Piece> Echiquier::placerPiece(
		std::unique_ptr<Piece> piece)
	{
		if (piece == nullptr) {
			return nullptr;
		}
		const Position position = piece->obtenirPosition();
		if (!estDansLimites(position)) {
			return piece;
		}

		std::unique_ptr<Piece> ancienne =
			std::move(cases_[position.ligne][position.colonne]);
		cases_[position.ligne][position.colonne] = std::move(piece);
		return ancienne;
	}


	std::unique_ptr<Piece> Echiquier::retirerPiece(const Position& position)
	{
		if (!estDansLimites(position)) {
			return nullptr;
		}
		return std::move(cases_[position.ligne][position.colonne]);
	}


	bool Echiquier::deplacerPiece(const Position& depart,
		const Position& arrivee)
	{
		if (!estDansLimites(depart) || !estDansLimites(arrivee)) {
			return false;
		}

		Piece* piece = obtenirPiece(depart);
		if (piece == nullptr) {
			return false;
		}

		if (!peutAtteindre(depart, arrivee)) {
			return false;
		}

		
		Piece* pieceArrivee = obtenirPiece(arrivee);
		if (pieceArrivee != nullptr
			&& pieceArrivee->obtenirCouleur() == piece->obtenirCouleur()) {
			return false;
		}

		
		Couleur couleurJoueur = piece->obtenirCouleur();
		bool    autoEnEchec = false;
		{
			DeplacementTemporaire essai{ *this, depart, arrivee };
			autoEnEchec = estEnEchec(couleurJoueur);
		}
		if (autoEnEchec) {
			return false;
		}

		
		std::unique_ptr<Piece> pieceMobile = retirerPiece(depart);
		pieceMobile->deplacer(arrivee);
		placerPiece(std::move(pieceMobile));
		return true;
	}


	bool Echiquier::estEnEchec(Couleur couleur) const
	{
		Position positionRoi = trouverPositionRoi(couleur);
		if (positionRoi.ligne == positionInvalide) {
			return false;
		}

		for (int i = 0; i < tailleEchiquier; ++i) {
			for (int j = 0; j < tailleEchiquier; ++j) {
				Piece* attaquant = cases_[i][j].get();
				if (attaquant == nullptr) {
					continue;
				}
				if (attaquant->obtenirCouleur() == couleur) {
					continue;
				}
				Position positionAttaquant{ i, j };
				if (peutAtteindre(positionAttaquant, positionRoi)) {
					return true;
				}
			}
		}
		return false;
	}


	Position Echiquier::trouverPositionRoi(Couleur couleur) const
	{
		for (int i = 0; i < tailleEchiquier; ++i) {
			for (int j = 0; j < tailleEchiquier; ++j) {
				Piece* piece = cases_[i][j].get();
				if (piece == nullptr) {
					continue;
				}
				if (piece->obtenirCouleur() != couleur) {
					continue;
				}
				Roi* roi = dynamic_cast<Roi*>(piece);
				if (roi != nullptr) {
					return Position{ i, j };
				}
			}
		}
		return Position{ positionInvalide, positionInvalide };
	}


	bool Echiquier::estDansLimites(const Position& position)
	{
		return position.ligne >= 0 && position.ligne < tailleEchiquier
			&& position.colonne >= 0 && position.colonne < tailleEchiquier;
	}


	void Echiquier::vider()
	{
		for (int i = 0; i < tailleEchiquier; ++i) {
			for (int j = 0; j < tailleEchiquier; ++j) {
				cases_[i][j].reset();
			}
		}
	}


	bool Echiquier::peutAtteindre(const Position& depart,
		const Position& arrivee) const
	{
		if (!estDansLimites(depart) || !estDansLimites(arrivee)) {
			return false;
		}
		Piece* piece = cases_[depart.ligne][depart.colonne].get();
		if (piece == nullptr) {
			return false;
		}
		if (!piece->estMouvementValide(arrivee)) {
			return false;
		}
		if (piece->peutSauterPieces()) {
			return true;
		}
		return cheminEstLibre(depart, arrivee);
	}


	bool Echiquier::cheminEstLibre(const Position& depart,
		const Position& arrivee) const
	{
		int deltaLigne = arrivee.ligne - depart.ligne;
		int deltaColonne = arrivee.colonne - depart.colonne;

		int pasLigne = 0;
		if (deltaLigne > 0) {
			pasLigne = 1;
		}
		else if (deltaLigne < 0) {
			pasLigne = -1;
		}

		int pasColonne = 0;
		if (deltaColonne > 0) {
			pasColonne = 1;
		}
		else if (deltaColonne < 0) {
			pasColonne = -1;
		}

		Position courante{ depart.ligne + pasLigne,
							depart.colonne + pasColonne };
		while (!(courante == arrivee)) {
			if (cases_[courante.ligne][courante.colonne] != nullptr) {
				return false;
			}
			courante.ligne += pasLigne;
			courante.colonne += pasColonne;
		}
		return true;
	}

}  