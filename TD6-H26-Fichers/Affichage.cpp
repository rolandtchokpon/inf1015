/**
 * Implementation de la fenetre Qt de l'echiquier.
 * \file   Affichage.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include "Affichage.hpp"

#include <QAction>
#include <QColor>
#include <QFont>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QString>
#include <QWidget>

#include "Couleur.hpp"
#include "ExceptionRoi.hpp"
#include "Piece.hpp"

namespace vue {

	namespace {

		const QColor teinteClaire{ 220, 225, 235 };
		const QColor teinteFoncee{ 130, 150, 180 };
		const QColor teinteSelection{ 210, 180,  90 };
		const QColor teinteRefus{ 180,  80, 110 };
		const QColor teinteEchec{ 200, 100, 100 };

		constexpr int dimensionCase = 60;
		constexpr int hauteurLettres = 22;


		bool estCaseClaire(int ligne, int colonne)
		{
			return ((ligne + colonne) % 2) == 0;
		}


		QColor teinteDeBase(int ligne, int colonne)
		{
			return estCaseClaire(ligne, colonne) ? teinteClaire : teinteFoncee;
		}


		// Retourne la couleur du texte selon le camp de la piece :
		// blanc = "#ffffff" (pieces claires), noir = "#101820" (pieces sombres).
		QString couleurTexte(modele::Couleur couleurPiece)
		{
			if (couleurPiece == modele::Couleur::blanc) {
				return "#ffffff";
			}
			return "#101820";
		}


		void installerApparence(QPushButton& bouton,
			const QColor& fond,
			const QString& couleurDuTexte)
		{
			bouton.setStyleSheet(QString(
				"QPushButton { "
				"background-color: %1; "
				"color: %2; "
				"font-weight: bold; "
				"border: 1px solid gray; "
				"}")
				.arg(fond.name())
				.arg(couleurDuTexte));
		}

	}  // namespace anonyme


	FenetreEchiquier::FenetreEchiquier(QWidget* parent)
		: QMainWindow(parent)
	{
		initialiserInterface();
		demarrerNouvellePartie(modele::PositionDepart::roiTour);
	}


	void FenetreEchiquier::initialiserInterface()
	{
		QWidget* widgetCentral = new QWidget(this);
		QGridLayout* grilleLayout = new QGridLayout(widgetCentral);
		grilleLayout->setSpacing(0);
		grilleLayout->setContentsMargins(4, 4, 4, 4);

		QFont policeCases{ "Consolas", hauteurLettres, QFont::Bold };

		for (int i = 0; i < modele::tailleEchiquier; ++i) {
			for (int j = 0; j < modele::tailleEchiquier; ++j) {
				QPushButton* bouton = new QPushButton(widgetCentral);
				bouton->setFixedSize(dimensionCase, dimensionCase);
				bouton->setFont(policeCases);
				installerApparence(*bouton,
					teinteDeBase(i, j), "black");

				connect(bouton, &QPushButton::clicked, this,
					&FenetreEchiquier::surClicCase);

				grilleLayout->addWidget(bouton, i, j);
				boutonsCases_[i][j] = bouton;
			}
		}

		setCentralWidget(widgetCentral);
		creerMenuPositions();
		setWindowTitle("Fin de partie - Echiquier");
	}


	void FenetreEchiquier::creerMenuPositions()
	{
		QMenu* menuPartie = menuBar()->addMenu("Partie");

		QMenu* menuNouvellePartie =
			menuPartie->addMenu("Nouvelle partie");

		QAction* actionRoiTour = menuNouvellePartie->addAction(
			"Roi + Tour vs Roi");
		connect(actionRoiTour, &QAction::triggered, this,
			&FenetreEchiquier::surNouvellePartieRoiTour);

		QAction* actionDeuxCavaliers = menuNouvellePartie->addAction(
			"Roi + 2 Cavaliers vs Roi");
		connect(actionDeuxCavaliers, &QAction::triggered, this,
			&FenetreEchiquier::surNouvellePartieRoiDeuxCavaliers);

		QAction* actionTourCavalier = menuNouvellePartie->addAction(
			"Roi + Tour + Cavalier vs Roi");
		connect(actionTourCavalier, &QAction::triggered, this,
			&FenetreEchiquier::surNouvellePartieRoiTourCavalier);
	}


	void FenetreEchiquier::surNouvellePartieRoiTour()
	{
		demarrerNouvellePartie(modele::PositionDepart::roiTour);
	}


	void FenetreEchiquier::surNouvellePartieRoiDeuxCavaliers()
	{
		demarrerNouvellePartie(modele::PositionDepart::roiDeuxCavaliers);
	}


	void FenetreEchiquier::surNouvellePartieRoiTourCavalier()
	{
		demarrerNouvellePartie(modele::PositionDepart::roiTourCavalier);
	}


	void FenetreEchiquier::demarrerNouvellePartie(
		modele::PositionDepart positionDepart)
	{
		effacerSelection();
		try {
			partie_.initialiser(positionDepart);
		}
		catch (const modele::ExceptionRoi& exception) {
			QMessageBox::warning(this, "Erreur",
				QString::fromLocal8Bit(exception.what()));
		}
		rafraichirAffichage();
		afficherEtatPartie();
	}


	void FenetreEchiquier::surClicCase()
	{
		QObject* emetteur = sender();
		for (int i = 0; i < modele::tailleEchiquier; ++i) {
			for (int j = 0; j < modele::tailleEchiquier; ++j) {
				if (boutonsCases_[i][j] == emetteur) {
					gererClicSurCase(modele::Position{ i, j });
					return;
				}
			}
		}
	}


	void FenetreEchiquier::gererClicSurCase(
		const modele::Position& position)
	{
		if (partie_.obtenirEtat() != modele::EtatPartie::enCours) {
			statusBar()->showMessage(
				"La partie est terminee. Demarrez-en une nouvelle.");
			return;
		}

		const modele::Echiquier& echiquier = partie_.obtenirEchiquier();

		if (!caseEstSelectionnee_) {
			modele::Piece* piece = echiquier.obtenirPiece(position);
			if (piece == nullptr) {
				statusBar()->showMessage("Case vide.");
				return;
			}
			if (piece->obtenirCouleur()
				!= partie_.obtenirCouleurCourante()) {
				statusBar()->showMessage(
					"Cette piece n'est pas a vous.");
				return;
			}
			selection_ = position;
			caseEstSelectionnee_ = true;
			marquerCaseSelectionnee();
			statusBar()->showMessage(
				"Piece selectionnee. Choisissez la destination.");
			return;
		}

		if (position == selection_) {
			effacerSelection();
			rafraichirAffichage();
			afficherEtatPartie();
			return;
		}

		bool succes = partie_.jouerCoup(selection_, position);
		effacerSelection();
		rafraichirAffichage();

		if (succes) {
			afficherEtatPartie();
		}
		else {
			statusBar()->showMessage("Coup refuse.");
			installerApparence(
				*boutonsCases_[position.ligne][position.colonne],
				teinteRefus, "black");
		}
	}


	void FenetreEchiquier::rafraichirAffichage()
	{
		const modele::Echiquier& echiquier = partie_.obtenirEchiquier();

		for (int i = 0; i < modele::tailleEchiquier; ++i) {
			for (int j = 0; j < modele::tailleEchiquier; ++j) {
				modele::Piece* piece = echiquier.obtenirPiece(
					modele::Position{ i, j });
				QString couleurDuTexte = "black";
				if (piece != nullptr) {
					boutonsCases_[i][j]->setText(
						QString(QChar(piece->obtenirSymbole())));
					couleurDuTexte = couleurTexte(piece->obtenirCouleur());
				}
				else {
					boutonsCases_[i][j]->setText("");
				}
				installerApparence(*boutonsCases_[i][j],
					teinteDeBase(i, j), couleurDuTexte);
			}
		}

		// Si le joueur courant est en echec, on colore la case de son roi.
		if (partie_.joueurCourantEnEchec()) {
			modele::Position positionRoi =
				echiquier.trouverPositionRoi(
					partie_.obtenirCouleurCourante());
			if (positionRoi.ligne >= 0) {
				modele::Piece* roi = echiquier.obtenirPiece(positionRoi);
				QString teinteCarac = "black";
				if (roi != nullptr) {
					teinteCarac = couleurTexte(roi->obtenirCouleur());
				}
				installerApparence(
					*boutonsCases_[positionRoi.ligne][positionRoi.colonne],
					teinteEchec, teinteCarac);
			}
		}
	}


	void FenetreEchiquier::afficherEtatPartie()
	{
		modele::EtatPartie etat = partie_.obtenirEtat();
		modele::Couleur    couleur = partie_.obtenirCouleurCourante();
		QString            nomCouleur =
			(couleur == modele::Couleur::blanc) ? "Blancs" : "Noirs";

		if (etat == modele::EtatPartie::echecEtMat) {
			QString nomGagnant =
				(couleur == modele::Couleur::blanc) ? "Noirs" : "Blancs";
			QMessageBox::information(this, "Fin de partie",
				QString("Echec et mat ! Les %1 gagnent.").arg(nomGagnant));
			statusBar()->showMessage(
				QString("Echec et mat. Les %1 gagnent.").arg(nomGagnant));
		}
		else if (etat == modele::EtatPartie::pat) {
			QMessageBox::information(this, "Fin de partie",
				"Pat ! La partie est nulle.");
			statusBar()->showMessage("Pat. La partie est nulle.");
		}
		else if (partie_.joueurCourantEnEchec()) {
			statusBar()->showMessage(
				QString("Tour des %1 - Echec !").arg(nomCouleur));
		}
		else {
			statusBar()->showMessage(
				QString("Tour des %1.").arg(nomCouleur));
		}
	}


	void FenetreEchiquier::marquerCaseSelectionnee()
	{
		if (!caseEstSelectionnee_) {
			return;
		}
		const modele::Echiquier& echiquier = partie_.obtenirEchiquier();
		modele::Piece* piece = echiquier.obtenirPiece(selection_);
		QString couleurDuTexte = "black";
		if (piece != nullptr) {
			couleurDuTexte = couleurTexte(piece->obtenirCouleur());
		}
		installerApparence(
			*boutonsCases_[selection_.ligne][selection_.colonne],
			teinteSelection, couleurDuTexte);
	}


	void FenetreEchiquier::effacerSelection()
	{
		caseEstSelectionnee_ = false;
	}

}  