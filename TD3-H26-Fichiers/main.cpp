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

//TODO: Vos surcharges d'opérateur <<

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion
	
	ListeJeux listeJeux = creerListeJeux("jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	Liste<string> L;
	L.ajouterElements(make_unique<string>("Roland"));
	L.ajouterElements(make_unique<string>("Edwige"));

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
	}
	/*Liste<int> l;

	for (int i = 0; i < 50; ++i)
		l.ajouterElements(make_unique<int>(i));

	assert(l.size() == 50);
	assert(l.getCapacite() >= 50);

	for (int i = 0; i < 50; ++i)
		assert(l[i] == i);

	std::cout << "Test 50 elements OK\n";*/


	//TODO: L'affichage de listeJeux et l'écriture dans le fichier devraient fonctionner.

	//TODO: Compléter le main avec les tests demandés.
	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}