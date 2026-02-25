// main.cpp
// Tests et demonstrations du projet.
#include <iostream>
#include <fstream>
#include "Liste.hpp"
#include "Concepteur.hpp"
#include <cassert>
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
using namespace std;

// Surcharges d'opérateur << pour l'affichage des objets.
ostream& operator<<(ostream& fluxSortie, const Concepteur& concepteur)
{
	fluxSortie << "\t" << concepteur.getNom()
		<< ", " << concepteur.getAnneeNaissance()
		<< ", " << concepteur.getPays();
	return fluxSortie;
}
ostream& operator<<(ostream& fluxSortie, const Jeu& jeu)
{
	static const string bleu = "\033[94m";
	static const string reset = "\033[0m";

	fluxSortie << "Titre : " << bleu << jeu.getTitre() << reset << "\n"
		<< "Parution : " << bleu << jeu.getAnneeSortie() << reset << "\n"
		<< "Développeur : " << bleu << jeu.getDeveloppeur() << reset << "\n"
		<< "Concepteurs du jeu :\n";

	const auto& concepteurs = jeu.getConcepteurs();
	for (unsigned i = 0; i < concepteurs.size(); i++)
		fluxSortie << concepteurs[i] << "\n";

	return fluxSortie;
}
ostream& operator<<(ostream& fluxSortie, const ListeJeux& listeJeux)
{
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	for (unsigned i = 0; i < listeJeux.size(); i++) {
		fluxSortie << ligneSeparation;
		fluxSortie << listeJeux[i];
	}
	fluxSortie << ligneSeparation;
	return fluxSortie;
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	constexpr unsigned indexJeuReference = 2;
	constexpr unsigned indexJeuRecherche = 1;
	constexpr unsigned indexConcepteurSecond = 1;
	constexpr unsigned indexJeuSource = 0;
	constexpr unsigned indexConcepteurPremier = 0;
	constexpr int nValeursTest = 50;

	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion
	
	// Creation de la liste de jeux a partir du fichier binaire.
	ListeJeux listeJeux = creerListeJeux("jeux.bin");

	// Tests: capacite et taille.
	cout << listeJeux.getCapacite() << endl;
	cout << listeJeux.size() << endl;

	// Tests: acces par index et aux concepteurs.
	cout << listeJeux[indexJeuReference].getTitre() << endl;
	cout << listeJeux[indexJeuReference].getConcepteurs()[indexConcepteurSecond].getNom() << endl;

	// Tests: recherche d'un concepteur via un predicat.
	auto concepteurTrouve = listeJeux[indexJeuRecherche].trouverConcepteur([](const Concepteur& concepteur) {
		return concepteur.getNom() == "Yoshinori Kitase";
		});
	if (concepteurTrouve != nullptr) {
		cout << concepteurTrouve->getAnneeNaissance() << endl;
	}
	// Tests: surcharge d'ostream (ecran et fichier).
	cout << listeJeux;

	//ofstream fichier("sortie_jeux.txt");
	//fichier << listeJeux;

	// Tests copie :
	Jeu copieJeu = listeJeux[indexJeuReference];
	//Avant copie
	cout << "Avant Copie: " << listeJeux[indexJeuReference] << copieJeu;
	copieJeu.getConcepteurs().getSharedPtr(indexConcepteurSecond) =
		listeJeux[indexJeuSource].getConcepteurs().getSharedPtr(indexConcepteurPremier);
	//Après copie
	cout << "Apres Copie : " << listeJeux[indexJeuReference] << copieJeu << endl;

	//Recuperation des adresses original et copie
	const Concepteur* adresseOriginale =
		listeJeux[indexJeuReference].getConcepteurs().getSharedPtr(indexConcepteurPremier).get();
	const Concepteur* adresseCopie =
		copieJeu.getConcepteurs().getSharedPtr(0).get();
	cout << "Adresse 1er concepteur (original): " << adresseOriginale << "\n";
	cout << "Adresse 1er concepteur (copie): " << adresseCopie << "\n";
	cout << "Meme adresse? " << boolalpha << (adresseOriginale == adresseCopie) << "\n"; //Retourne true lorsque les adresses sont les memes


	/*Liste<string> L;
	L.ajouterElements(make_shared<string>("Roland"));
	L.ajouterElements(make_shared<string>("Edwige"));

	L.augmenterCapacite(10);
	cout << L[1] << endl;

	string *pos = L.rechercherElements([](string x){
		return x == "Youssef";
	});

	if (pos) {
		cout << *pos << endl;
	}
	else {
		cout << "Pas present";
	}*/
	Liste<int> listeEntiers;

	for (int i = 0; i < nValeursTest; ++i)
		listeEntiers.ajouterElements(make_shared<int>(i));


	//TODO: L'affichage de listeJeux et l'écriture dans le fichier devraient fonctionner.

	//TODO: Compléter le main avec les tests demandés.
	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}
