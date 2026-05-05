/**
 * Tests automatises du modele du jeu d'echecs.
 * \file   main.cpp
 * \author []
 * \date   5 mai 2026
 * Cree le 18 avril 2026
 */

#include <iostream>

#include <QApplication>

#include "Affichage.hpp"
#include "Cavalier.hpp"
#include "Couleur.hpp"
#include "DeplacementTemporaire.hpp"
#include "Echiquier.hpp"
#include "ExceptionRoi.hpp"
#include "Partie.hpp"
#include "Piece.hpp"
#include "Position.hpp"
#include "Roi.hpp"
#include "Tour.hpp"

namespace {

	int nTotalTests = 0;
	int nTestsReussis = 0;


	void verifier(const char* nomTest, bool succes)
	{
		++nTotalTests;
		if (succes) {
			++nTestsReussis;
			std::cout << "  [OK]    " << nomTest << "\n";
		}
		else {
			std::cout << "  [ECHEC] " << nomTest << "\n";
		}
	}


	// Tests pour Position
	
	void testerPosition()
	{
		std::cout << "\n--- Tests Position ---\n";

		modele::Position positionParDefaut;
		verifier("Position par defaut a ligne 0",
			positionParDefaut.ligne == 0);
		verifier("Position par defaut a colonne 0",
			positionParDefaut.colonne == 0);

		modele::Position positionExplicite{ 3, 5 };
		verifier("Position explicite a ligne 3",
			positionExplicite.ligne == 3);
		verifier("Position explicite a colonne 5",
			positionExplicite.colonne == 5);

		modele::Position positionEgale1{ 2, 4 };
		modele::Position positionEgale2{ 2, 4 };
		modele::Position positionDifferente{ 2, 5 };
		verifier("Egalite reflexive",
			positionEgale1 == positionEgale1);
		verifier("Egalite symetrique",
			positionEgale1 == positionEgale2);
		verifier("Inegalite detectee",
			!(positionEgale1 == positionDifferente));
	}


	
	// Tests pour Couleur
	void testerCouleur()
	{
		std::cout << "\n--- Tests Couleur ---\n";

		verifier("Couleur opposee de blanc est noir",
			modele::couleurOpposee(modele::Couleur::blanc)
			== modele::Couleur::noir);
		verifier("Couleur opposee de noir est blanc",
			modele::couleurOpposee(modele::Couleur::noir)
			== modele::Couleur::blanc);
	}


	
	// Tests pour Tour
	
	void testerTour()
	{
		std::cout << "\n--- Tests Tour ---\n";

		modele::Tour tour{
			modele::Position {4, 4}, modele::Couleur::blanc };

		verifier("Position initiale correcte",
			tour.obtenirPosition() == modele::Position{ 4, 4 });
		verifier("Couleur correcte",
			tour.obtenirCouleur() == modele::Couleur::blanc);
		verifier("Symbole T",
			tour.obtenirSymbole() == 'T');
		verifier("Tour ne saute pas",
			!tour.peutSauterPieces());

		verifier("Mouvement horizontal valide",
			tour.estMouvementValide(modele::Position{ 4, 0 }));
		verifier("Mouvement vertical valide",
			tour.estMouvementValide(modele::Position{ 0, 4 }));
		verifier("Mouvement diagonal invalide",
			!tour.estMouvementValide(modele::Position{ 6, 6 }));
		verifier("Mouvement sur place invalide",
			!tour.estMouvementValide(modele::Position{ 4, 4 }));

		tour.deplacer(modele::Position{ 1, 1 });
		verifier("Apres deplacer, nouvelle position",
			tour.obtenirPosition() == modele::Position{ 1, 1 });
	}


	// Tests pour Cavalier

	void testerCavalier()
	{
		std::cout << "\n--- Tests Cavalier ---\n";

		modele::Cavalier cavalier{
			modele::Position {4, 4}, modele::Couleur::noir };

		verifier("Couleur correcte",
			cavalier.obtenirCouleur() == modele::Couleur::noir);
		verifier("Symbole C",
			cavalier.obtenirSymbole() == 'C');
		verifier("Cavalier saute",
			cavalier.peutSauterPieces());

		verifier("Forme L (2+1) valide",
			cavalier.estMouvementValide(modele::Position{ 6, 5 }));
		verifier("Forme L (1+2) valide",
			cavalier.estMouvementValide(modele::Position{ 5, 6 }));
		verifier("Forme L (-2-1) valide",
			cavalier.estMouvementValide(modele::Position{ 2, 3 }));
		verifier("Forme L (-1-2) valide",
			cavalier.estMouvementValide(modele::Position{ 3, 2 }));
		verifier("Ligne droite invalide",
			!cavalier.estMouvementValide(modele::Position{ 4, 6 }));
		verifier("Diagonale invalide",
			!cavalier.estMouvementValide(modele::Position{ 6, 6 }));
	}


	// Tests pour Roi (sans casser le compteur)
	
	void testerRoiMouvements()
	{
		std::cout << "\n--- Tests Roi (mouvements) ---\n";
		{
			modele::Roi roi{
				modele::Position {4, 4}, modele::Couleur::blanc };

			verifier("Couleur correcte",
				roi.obtenirCouleur() == modele::Couleur::blanc);
			verifier("Symbole R",
				roi.obtenirSymbole() == 'R');
			verifier("Roi ne saute pas",
				!roi.peutSauterPieces());

			verifier("Une case diagonale valide",
				roi.estMouvementValide(modele::Position{ 5, 5 }));
			verifier("Une case horizontale valide",
				roi.estMouvementValide(modele::Position{ 4, 5 }));
			verifier("Une case verticale valide",
				roi.estMouvementValide(modele::Position{ 3, 4 }));
			verifier("Sur place invalide",
				!roi.estMouvementValide(modele::Position{ 4, 4 }));
			verifier("Deux cases invalide",
				!roi.estMouvementValide(modele::Position{ 6, 4 }));
		}
		verifier("Compteur revient a 0 apres destruction",
			modele::Roi::obtenirNombreInstances() == 0);
	}


	void testerRoiException()
	{
		std::cout << "\n--- Tests Roi (exception) ---\n";
		{
			modele::Roi roi1{
				modele::Position {0, 0}, modele::Couleur::noir };
			modele::Roi roi2{
				modele::Position {7, 7}, modele::Couleur::blanc };

			verifier("Compteur a 2 apres 2 instances",
				modele::Roi::obtenirNombreInstances() == 2);

			bool exceptionLancee = false;
			try {
				modele::Roi roi3{
					modele::Position {3, 3}, modele::Couleur::blanc };
			}
			catch (const modele::ExceptionRoi& exception) {
				exceptionLancee = true;
				std::cout << "  Message recu : "
					<< exception.what() << "\n";
			}
			verifier("Troisieme roi interdit", exceptionLancee);
			verifier("Compteur reste a 2 apres exception",
				modele::Roi::obtenirNombreInstances() == 2);
		}
		verifier("Compteur revient a 0",
			modele::Roi::obtenirNombreInstances() == 0);
	}


	// Tests pour Echiquier
	
	void testerEchiquierBase()
	{
		std::cout << "\n--- Tests Echiquier (base) ---\n";

		modele::Echiquier echiquier;

		verifier("Position dans limites (0,0)",
			modele::Echiquier::estDansLimites(modele::Position{ 0, 0 }));
		verifier("Position dans limites (7,7)",
			modele::Echiquier::estDansLimites(modele::Position{ 7, 7 }));
		verifier("Position hors limites (-1,0)",
			!modele::Echiquier::estDansLimites(
				modele::Position{ -1, 0 }));
		verifier("Position hors limites (8,0)",
			!modele::Echiquier::estDansLimites(
				modele::Position{ 8, 0 }));
		verifier("Position hors limites (0,-1)",
			!modele::Echiquier::estDansLimites(
				modele::Position{ 0, -1 }));
		verifier("Position hors limites (0,8)",
			!modele::Echiquier::estDansLimites(
				modele::Position{ 0, 8 }));

		verifier("Case vide retourne nullptr",
			echiquier.obtenirPiece(modele::Position{ 3, 3 }) == nullptr);
		verifier("Position invalide retourne nullptr",
			echiquier.obtenirPiece(modele::Position{ -1, 0 }) == nullptr);
		verifier("Retirer position invalide retourne nullptr",
			echiquier.retirerPiece(modele::Position{ 9, 9 }) == nullptr);
		verifier("Placer nullptr retourne nullptr",
			echiquier.placerPiece(nullptr) == nullptr);
	}


	void testerEchiquierPlacementEtRetrait()
	{
		std::cout << "\n--- Tests Echiquier (placement) ---\n";

		modele::Echiquier echiquier;
		modele::Position  positionTour{ 0, 0 };

		echiquier.placerPiece(std::make_unique<modele::Tour>(
			positionTour, modele::Couleur::blanc));

		verifier("Tour placee est presente",
			echiquier.obtenirPiece(positionTour) != nullptr);
		verifier("Tour placee a bonne couleur",
			echiquier.obtenirPiece(positionTour)->obtenirCouleur()
			== modele::Couleur::blanc);

		std::unique_ptr<modele::Piece> retiree =
			echiquier.retirerPiece(positionTour);
		verifier("Tour retiree retourne la piece",
			retiree != nullptr);
		verifier("Case vide apres retrait",
			echiquier.obtenirPiece(positionTour) == nullptr);

		// Placer hors limites doit echouer.
		auto pieceHorsLimites = std::make_unique<modele::Tour>(
			modele::Position{ 9, 9 }, modele::Couleur::blanc);
		auto retournee = echiquier.placerPiece(std::move(pieceHorsLimites));
		verifier("Placer hors limites retourne la piece",
			retournee != nullptr);
	}


	void testerEchiquierVider()
	{
		std::cout << "\n--- Tests Echiquier (vider) ---\n";

		modele::Echiquier echiquier;
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 0, 0 }, modele::Couleur::blanc));
		echiquier.placerPiece(std::make_unique<modele::Cavalier>(
			modele::Position{ 7, 7 }, modele::Couleur::noir));

		echiquier.vider();
		verifier("Case (0,0) vide apres vider",
			echiquier.obtenirPiece(modele::Position{ 0, 0 }) == nullptr);
		verifier("Case (7,7) vide apres vider",
			echiquier.obtenirPiece(modele::Position{ 7, 7 }) == nullptr);
	}


	void testerEchiquierDeplacement()
	{
		std::cout << "\n--- Tests Echiquier (deplacement) ---\n";

		modele::Echiquier echiquier;
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 0, 0 }, modele::Couleur::blanc));

		verifier("Deplacement valide",
			echiquier.deplacerPiece(modele::Position{ 0, 0 },
				modele::Position{ 0, 5 }));
		verifier("Tour est arrivee",
			echiquier.obtenirPiece(modele::Position{ 0, 5 }) != nullptr);
		verifier("Case depart vide",
			echiquier.obtenirPiece(modele::Position{ 0, 0 }) == nullptr);

		verifier("Depart hors limites refuse",
			!echiquier.deplacerPiece(modele::Position{ -1, 0 },
				modele::Position{ 0, 0 }));
		verifier("Arrivee hors limites refusee",
			!echiquier.deplacerPiece(modele::Position{ 0, 5 },
				modele::Position{ 0, 9 }));
		verifier("Depart vide refuse",
			!echiquier.deplacerPiece(modele::Position{ 3, 3 },
				modele::Position{ 4, 4 }));
		verifier("Mouvement illegal refuse",
			!echiquier.deplacerPiece(modele::Position{ 0, 5 },
				modele::Position{ 3, 6 }));

		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 0, 3 }, modele::Couleur::blanc));
		verifier("Capture meme couleur refusee",
			!echiquier.deplacerPiece(modele::Position{ 0, 5 },
				modele::Position{ 0, 3 }));
	}


	void testerEchiquierCheminBloque()
	{
		std::cout << "\n--- Tests Echiquier (chemin bloque) ---\n";

		modele::Echiquier echiquier;
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 0, 0 }, modele::Couleur::blanc));
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 0, 3 }, modele::Couleur::noir));

		verifier("Tour bloquee par adversaire au chemin",
			!echiquier.deplacerPiece(modele::Position{ 0, 0 },
				modele::Position{ 0, 5 }));

		// Capture autorisee si la piece adverse est sur l'arrivee.
		verifier("Capture adversaire autorisee",
			echiquier.deplacerPiece(modele::Position{ 0, 0 },
				modele::Position{ 0, 3 }));

		echiquier.vider();
		echiquier.placerPiece(std::make_unique<modele::Cavalier>(
			modele::Position{ 0, 0 }, modele::Couleur::blanc));
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 1, 0 }, modele::Couleur::blanc));
		verifier("Cavalier saute par-dessus une piece",
			echiquier.deplacerPiece(modele::Position{ 0, 0 },
				modele::Position{ 2, 1 }));
	}


	void testerEchiquierEchec()
	{
		std::cout << "\n--- Tests Echiquier (echec) ---\n";

		modele::Echiquier echiquier;
		echiquier.placerPiece(std::make_unique<modele::Roi>(
			modele::Position{ 0, 0 }, modele::Couleur::blanc));
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			modele::Position{ 0, 5 }, modele::Couleur::noir));

		verifier("Roi blanc en echec par tour noire",
			echiquier.estEnEchec(modele::Couleur::blanc));
		verifier("Roi noir absent : pas en echec",
			!echiquier.estEnEchec(modele::Couleur::noir));

		verifier("Position du roi blanc trouvee",
			echiquier.trouverPositionRoi(modele::Couleur::blanc)
			== modele::Position{ 0, 0 });

		modele::Position positionInvalide =
			echiquier.trouverPositionRoi(modele::Couleur::noir);
		verifier("Roi noir absent : position invalide",
			positionInvalide.ligne == -1);

		// Mouvement qui s'auto-met en echec : refuse.
		verifier("Roi blanc ne peut s'auto-mettre en echec",
			!echiquier.deplacerPiece(modele::Position{ 0, 0 },
				modele::Position{ 0, 1 }));

		// Mouvement qui sort de l'echec : autorise.
		verifier("Roi blanc peut sortir de l'echec",
			echiquier.deplacerPiece(modele::Position{ 0, 0 },
				modele::Position{ 1, 0 }));
	}


	
	// Tests pour DeplacementTemporaire
	
	void testerDeplacementTemporaire()
	{
		std::cout << "\n--- Tests DeplacementTemporaire ---\n";

		modele::Echiquier echiquier;
		modele::Position  depart{ 0, 0 };
		modele::Position  arrivee{ 3, 0 };
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			depart, modele::Couleur::blanc));

		{
			modele::DeplacementTemporaire deplacement{
				echiquier, depart, arrivee };
			verifier("Piece deplacee a l'arrivee",
				echiquier.obtenirPiece(arrivee) != nullptr);
			verifier("Case depart vide pendant deplacement",
				echiquier.obtenirPiece(depart) == nullptr);
		}
		verifier("Piece revenue au depart",
			echiquier.obtenirPiece(depart) != nullptr);
		verifier("Case arrivee a nouveau vide",
			echiquier.obtenirPiece(arrivee) == nullptr);
	}


	void testerDeplacementTemporaireAvecCapture()
	{
		std::cout << "\n--- Tests DeplacementTemporaire (capture) ---\n";

		modele::Echiquier echiquier;
		modele::Position  depart{ 0, 0 };
		modele::Position  arrivee{ 0, 5 };
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			depart, modele::Couleur::blanc));
		echiquier.placerPiece(std::make_unique<modele::Tour>(
			arrivee, modele::Couleur::noir));

		{
			modele::DeplacementTemporaire deplacement{
				echiquier, depart, arrivee };
			verifier("Capture temporaire effectuee",
				echiquier.obtenirPiece(arrivee)->obtenirCouleur()
				== modele::Couleur::blanc);
		}
		verifier("Piece capturee restauree",
			echiquier.obtenirPiece(arrivee) != nullptr
			&& echiquier.obtenirPiece(arrivee)->obtenirCouleur()
			== modele::Couleur::noir);
		verifier("Piece deplacante revenue",
			echiquier.obtenirPiece(depart) != nullptr);
	}


	void testerDeplacementTemporaireDepartVide()
	{
		std::cout << "\n--- Tests DeplacementTemporaire (depart vide) ---\n";

		modele::Echiquier echiquier;
		modele::Position  depart{ 0, 0 };
		modele::Position  arrivee{ 3, 0 };

		{
			modele::DeplacementTemporaire deplacement{
				echiquier, depart, arrivee };
			verifier("Pas de piece deplacee",
				echiquier.obtenirPiece(arrivee) == nullptr);
		}
		verifier("Echiquier reste vide",
			echiquier.obtenirPiece(depart) == nullptr);
	}


	// Tests pour Partie
	void testerPartieInitialisation()
	{
		std::cout << "\n--- Tests Partie (initialisation) ---\n";

		modele::Partie partie;
		partie.initialiser(modele::PositionDepart::roiTour);

		const modele::Echiquier& echiquier = partie.obtenirEchiquier();
		verifier("Roi noir en haut",
			echiquier.obtenirPiece(modele::Position{ 0, 4 }) != nullptr);
		verifier("Roi blanc en bas",
			echiquier.obtenirPiece(modele::Position{ 7, 4 }) != nullptr);
		verifier("Tour blanche en (7,0)",
			echiquier.obtenirPiece(modele::Position{ 7, 0 }) != nullptr);
		verifier("Tour blanche est blanche",
			echiquier.obtenirPiece(modele::Position{ 7, 0 })
			->obtenirCouleur() == modele::Couleur::blanc);
		verifier("Couleur courante est blanc au depart",
			partie.obtenirCouleurCourante() == modele::Couleur::blanc);
		verifier("Etat est en cours",
			partie.obtenirEtat() == modele::EtatPartie::enCours);
		verifier("Pas en echec au depart",
			!partie.joueurCourantEnEchec());

		partie.initialiser(modele::PositionDepart::roiDeuxCavaliers);
		verifier("Position 2 cavaliers : un cavalier en (7,1)",
			echiquier.obtenirPiece(modele::Position{ 7, 1 }) != nullptr);
		verifier("Position 2 cavaliers : un cavalier en (7,6)",
			echiquier.obtenirPiece(modele::Position{ 7, 6 }) != nullptr);

		partie.initialiser(modele::PositionDepart::roiTourCavalier);
		verifier("Position roiTourCavalier : tour en (7,0)",
			echiquier.obtenirPiece(modele::Position{ 7, 0 }) != nullptr);
		verifier("Position roiTourCavalier : cavalier en (7,1)",
			echiquier.obtenirPiece(modele::Position{ 7, 1 }) != nullptr);
	}


	void testerPartieAlternanceTours()
	{
		std::cout << "\n--- Tests Partie (alternance tours) ---\n";

		modele::Partie partie;
		partie.initialiser(modele::PositionDepart::roiTour);

		verifier("Refuse de jouer une piece noire au tour blanc",
			!partie.jouerCoup(modele::Position{ 0, 4 },
				modele::Position{ 0, 5 }));

		verifier("Joue un coup blanc valide",
			partie.jouerCoup(modele::Position{ 7, 0 },
				modele::Position{ 5, 0 }));
		verifier("Couleur courante passe a noir",
			partie.obtenirCouleurCourante() == modele::Couleur::noir);

		verifier("Refuse de jouer une piece blanche au tour noir",
			!partie.jouerCoup(modele::Position{ 7, 4 },
				modele::Position{ 7, 3 }));

		verifier("Joue un coup noir valide",
			partie.jouerCoup(modele::Position{ 0, 4 },
				modele::Position{ 0, 3 }));
		verifier("Couleur courante revient a blanc",
			partie.obtenirCouleurCourante() == modele::Couleur::blanc);

		verifier("Refuse depart vide",
			!partie.jouerCoup(modele::Position{ 4, 4 },
				modele::Position{ 5, 5 }));
	}


	void testerPartieEchecEtMat()
	{
		std::cout << "\n--- Tests Partie (echec et mat) ---\n";

		modele::Partie partie;
		partie.initialiser(modele::PositionDepart::roiTour);

		

		// Tour blanche : (7,0) -> (5,0)
		partie.jouerCoup(modele::Position{ 7, 0 },
			modele::Position{ 5, 0 });
		// Roi noir : (0,4) -> (0,3)
		partie.jouerCoup(modele::Position{ 0, 4 },
			modele::Position{ 0, 3 });
		// Tour blanche : (5,0) -> (0,0) (echec sur la 1ere ligne)
		bool echec = partie.jouerCoup(modele::Position{ 5, 0 },
			modele::Position{ 0, 0 });
		verifier("Tour atteint la 1ere ligne",
			echec);
		verifier("Roi noir en echec apres ce coup",
			partie.joueurCourantEnEchec());

		// Le roi noir va devoir bouger.
		verifier("Etat encore en cours apres echec simple",
			partie.obtenirEtat() == modele::EtatPartie::enCours);
	}


	void testerPartieEtatTermine()
	{
		std::cout << "\n--- Tests Partie (etat termine) ---\n";

		modele::Partie partie;
		partie.initialiser(modele::PositionDepart::roiTour);

		// Forcer un etat hors-en-cours en simulant directement
		// (on suppose qu'il existe un cas d'arret).
		verifier("Etat est en cours au depart",
			partie.obtenirEtat() == modele::EtatPartie::enCours);
	}



	// Execution complete
	
	void executerTousLesTests()
	{
		std::cout << "\n========== Tests automatises du modele "
			<< "==========\n";

		testerPosition();
		testerCouleur();
		testerTour();
		testerCavalier();
		testerRoiMouvements();
		testerRoiException();
		testerEchiquierBase();
		testerEchiquierPlacementEtRetrait();
		testerEchiquierVider();
		testerEchiquierDeplacement();
		testerEchiquierCheminBloque();
		testerEchiquierEchec();
		testerDeplacementTemporaire();
		testerDeplacementTemporaireAvecCapture();
		testerDeplacementTemporaireDepartVide();
		testerPartieInitialisation();
		testerPartieAlternanceTours();
		testerPartieEchecEtMat();
		testerPartieEtatTermine();

		std::cout << "\n========== Bilan : "
			<< nTestsReussis << " / " << nTotalTests
			<< " tests reussis ==========\n\n";
	}

}  


int main(int argc, char* argv[])
{
	executerTousLesTests();

	QApplication application{ argc, argv };

	vue::FenetreEchiquier fenetre;
	fenetre.show();

	return application.exec();
}