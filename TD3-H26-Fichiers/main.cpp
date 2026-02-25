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
ostream& operator<<(ostream& os, const Concepteur& c)
{
	os << "\t" << c.getNom()
		<< ", " << c.getAnneeNaissance()
		<< ", " << c.getPays();
	return os;
}
ostream& operator<<(ostream& os, const Jeu& jeu)
{
	static const string bleu = "\033[94m";
	static const string reset = "\033[0m";

	os << "Titre : " << bleu << jeu.getTitre() << reset << "\n"
		<< "Parution : " << bleu << jeu.getAnneeSortie() << reset << "\n"
		<< "Développeur : " << bleu << jeu.getDeveloppeur() << reset << "\n"
		<< "Concepteurs du jeu :\n";

	const auto& concepteurs = jeu.getConcepteurs();
	for (unsigned i = 0; i < concepteurs.size(); i++)
		os << *concepteurs[i] << "\n";

	return os;
}
ostream& operator<<(ostream& os, const ListeJeux& listeJeux)
{
	static const string ligne =
		"\n\033[95m══════════════════════════════════════════════════════════════════════════\033[0m\n";

	for (unsigned i = 0; i < listeJeux.size(); i++) {
		os << ligne;
		os << *listeJeux[i];
	}
	os << ligne;
	return os;
}


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


	cout << listeJeux.getCapacite() << endl;
	cout << listeJeux.size() << endl;

	cout << listeJeux[2].getTitre() << endl;
	cout << listeJeux[2].getConcepteurs()[1].getNom() << endl;

	auto c = listeJeux[1].trouverConcepteur([](const Concepteur& c) {
		return c.getNom() == "Yoshinori Kitase";
		});
	if (c) {
		cout << c->getAnneeNaissance() << endl;
	}
	//Pour tester :
	cout << listeJeux;

	ofstream fichier("sortie_jeux.txt");
	fichier << listeJeux;
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
	Liste<int> l;

	for (int i = 0; i < 50; ++i)
		l.ajouterElements(make_shared<int>(i));


	//TODO: L'affichage de listeJeux et l'écriture dans le fichier devraient fonctionner.

	//TODO: Compléter le main avec les tests demandés.
	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}
