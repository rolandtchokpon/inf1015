/**
 * Implementation de la classe Partie.
 * \file   Partie.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 25 avril 2026
 */

#include "Partie.hpp"

#include <memory>

#include "Cavalier.hpp"
#include "DeplacementTemporaire.hpp"
#include "Roi.hpp"
#include "Tour.hpp"

namespace modele {

	void Partie::initialiser(PositionDepart positionDepart)
	{
		echiquier_.vider();
		couleurCourante_ = Couleur::blanc;
		etat_ = EtatPartie::enCours;

		// Les rois sont presents dans toutes les positions de depart.
		echiquier_.placerPiece(std::make_unique<Roi>(
			Position{ 0, 4 }, Couleur::noir));
		echiquier_.placerPiece(std::make_unique<Roi>(
			Position{ 7, 4 }, Couleur::blanc));

		if (positionDepart == PositionDepart::roiTour) {
			echiquier_.placerPiece(std::make_unique<Tour>(
				Position{ 7, 0 }, Couleur::blanc));
		}
		else if (positionDepart == PositionDepart::roiDeuxCavaliers) {
			echiquier_.placerPiece(std::make_unique<Cavalier>(
				Position{ 7, 1 }, Couleur::blanc));
			echiquier_.placerPiece(std::make_unique<Cavalier>(
				Position{ 7, 6 }, Couleur::blanc));
		}
		else {
			// PositionDepart::roiTourCavalier
			echiquier_.placerPiece(std::make_unique<Tour>(
				Position{ 7, 0 }, Couleur::blanc));
			echiquier_.placerPiece(std::make_unique<Cavalier>(
				Position{ 7, 1 }, Couleur::blanc));
		}
	}


	bool Partie::jouerCoup(const Position& depart,
		const Position& arrivee)
	{
		if (etat_ != EtatPartie::enCours) {
			return false;
		}

		Piece* piece = echiquier_.obtenirPiece(depart);
		if (piece == nullptr) {
			return false;
		}
		if (piece->obtenirCouleur() != couleurCourante_) {
			return false;
		}

		bool succes = echiquier_.deplacerPiece(depart, arrivee);
		if (!succes) {
			return false;
		}

		couleurCourante_ = couleurOpposee(couleurCourante_);
		mettreAJourEtatPartie();
		return true;
	}


	const Echiquier& Partie::obtenirEchiquier() const
	{
		return echiquier_;
	}


	Couleur Partie::obtenirCouleurCourante() const
	{
		return couleurCourante_;
	}


	EtatPartie Partie::obtenirEtat() const
	{
		return etat_;
	}


	bool Partie::joueurCourantEnEchec() const
	{
		return echiquier_.estEnEchec(couleurCourante_);
	}


	void Partie::mettreAJourEtatPartie()
	{
		bool aUnCoupLegal = joueurAUnCoupLegal(couleurCourante_);
		if (aUnCoupLegal) {
			etat_ = EtatPartie::enCours;
			return;
		}
		if (echiquier_.estEnEchec(couleurCourante_)) {
			etat_ = EtatPartie::echecEtMat;
		}
		else {
			etat_ = EtatPartie::pat;
		}
	}


	bool Partie::joueurAUnCoupLegal(Couleur couleur) const
	{
		for (int i = 0; i < tailleEchiquier; ++i) {
			for (int j = 0; j < tailleEchiquier; ++j) {
				Position depart{ i, j };
				Piece* piece = echiquier_.obtenirPiece(depart);
				if (piece == nullptr) {
					continue;
				}
				if (piece->obtenirCouleur() != couleur) {
					continue;
				}
				for (int k = 0; k < tailleEchiquier; ++k) {
					for (int m = 0; m < tailleEchiquier; ++m) {
						Position arrivee{ k, m };
						if (depart == arrivee) {
							continue;
						}
						Echiquier& nonConst =
							const_cast<Echiquier&>(echiquier_);
						Piece* destination = nonConst.obtenirPiece(arrivee);
						if (destination != nullptr
							&& destination->obtenirCouleur() == couleur) {
							continue;
						}

					
						if (!piece->estMouvementValide(arrivee)) {
							continue;
						}
						
						DeplacementTemporaire essai{
							nonConst, depart, arrivee };
						bool resteEnEchec = nonConst.estEnEchec(couleur);
						if (!resteEnEchec) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

}  