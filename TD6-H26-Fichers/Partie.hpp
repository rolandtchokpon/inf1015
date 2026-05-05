/**
 * Classe Partie : orchestre l'echiquier, l'alternance des tours
 * et la detection des fins de partie.
 * \file   Partie.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 25 avril 2026
 */

#pragma once

#include "Couleur.hpp"
#include "Echiquier.hpp"
#include "Position.hpp"

namespace modele {

	enum class PositionDepart
	{
		roiTour,          
		roiDeuxCavaliers,  
		roiTourCavalier    
	};

	enum class EtatPartie
	{
		enCours,
		echecEtMat,
		pat
	};


	class Partie
	{
	public:
		Partie() = default;

		Partie(const Partie&) = delete;
		Partie& operator=(const Partie&) = delete;

		void initialiser(PositionDepart positionDepart);

		
		bool jouerCoup(const Position& depart,
			const Position& arrivee);

		const Echiquier& obtenirEchiquier() const;
		Couleur          obtenirCouleurCourante() const;
		EtatPartie       obtenirEtat() const;

		
		bool joueurCourantEnEchec() const;

	private:
		void mettreAJourEtatPartie();

		bool joueurAUnCoupLegal(Couleur couleur) const;

		Echiquier  echiquier_{};
		Couleur    couleurCourante_ = Couleur::blanc;
		EtatPartie etat_ = EtatPartie::enCours;
	};

}  