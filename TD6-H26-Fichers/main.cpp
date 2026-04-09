/**
 * \file main.cpp
 * \brief Point d'entree du TD6.
 */

#include <iostream>

#include "Affichage.hpp"
#include "DeplacementTemporaire.hpp"
#include "Roi.hpp"

int main()
{
	try {
		// TODO(Personne 2) :
		// 1. Remplacer ce scenario de test par celui de votre vrai projet.
		// 2. Creer un premier roi valide.
		// 3. Creer un deuxieme roi valide.
		// 4. Afficher la position d'au moins une piece.
		// 5. Tester le deplacement temporaire dans un bloc local.
		// 6. Tenter de creer un troisieme roi pour declencher l'exception.

		modele::Roi roiBlanc({0, 4});
		modele::Roi roiNoir({7, 4});

		vue::afficherPositionPiece(roiBlanc);

		{
			modele::DeplacementTemporaire deplacement(roiBlanc, {1, 4});
			std::cout << "Pendant le deplacement temporaire :" << std::endl;
			vue::afficherPositionPiece(roiBlanc);
		}

		std::cout << "Apres destruction de l'objet RAII :" << std::endl;
		vue::afficherPositionPiece(roiBlanc);

		// TODO(Personne 2) :
		// 1. Decider si l'exception doit etre attrapee ici ou dans une classe de vue.
		// 2. Ne pas attraper l'exception dans le constructeur de Roi.
		modele::Roi roiEnTrop({3, 3});

		std::cout << roiEnTrop.obtenirNombreInstances() << std::endl;
	}
	catch (const modele::ExceptionRoi& exception) {
		// TODO(Personne 2) :
		// 1. Afficher ici un message comprehensible pour l'utilisateur.
		// 2. Continuer l'execution a un endroit coherent sans garder 3 rois.
		vue::afficherMessageErreur(exception.what());
	}

	// TODO(Equipe) :
	// 1. Verifier qu'il y a au moins deux namespaces differents : modele et vue.
	// 2. Verifier qu'il n'y a aucun using namespace global.
	// 3. Compiler avec /W4 et corriger tous les avertissements.
	// 4. Completer les entetes de fichiers avec vos noms et la date.
	// 5. Verifier que le nom des classes, variables et fonctions respecte le guide.
	// 6. Tester la remise avec seulement les fichiers utiles du projet.

	return 0;
}
