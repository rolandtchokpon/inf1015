/**
 * Fenetre Qt affichant l'echiquier et gerant les interactions.
 * \file   Affichage.hpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#pragma once

#include <array>

#include <QMainWindow>
#include <QPushButton>

#include "Echiquier.hpp"
#include "Partie.hpp"
#include "Position.hpp"

namespace vue {

	class FenetreEchiquier : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit FenetreEchiquier(QWidget* parent = nullptr);
		~FenetreEchiquier() override = default;

		FenetreEchiquier(const FenetreEchiquier&) = delete;
		FenetreEchiquier& operator=(const FenetreEchiquier&) = delete;

	private:
		void initialiserInterface();
		void creerMenuPositions();
		void demarrerNouvellePartie(modele::PositionDepart positionDepart);
		void gererClicSurCase(const modele::Position& position);
		void rafraichirAffichage();
		void afficherEtatPartie();
		void marquerCaseSelectionnee();
		void effacerSelection();

		modele::Partie    partie_{};
		bool              caseEstSelectionnee_ = false;
		modele::Position  selection_{};

		std::array<std::array<QPushButton*,
			modele::tailleEchiquier>,
			modele::tailleEchiquier> boutonsCases_{};

	private slots:
		void surClicCase();
		void surNouvellePartieRoiTour();
		void surNouvellePartieRoiDeuxCavaliers();
		void surNouvellePartieRoiTourCavalier();
	};

}  