/**
 * main du TD5 - Liste liée, itérateurs et conteneurs STL.
 * \fichier:  main.cpp
 * \auteurs: Youssef Haddak et Roland Tchokpon
 * \date:   1er avril 2026
 * Créé le 24 mars 2026
 */
#include <map>
#include "Personnage.hpp"										
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}

int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	#if 1 //TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	cout << separateurSections << "Heros:" << endl;
	for (auto& h : heros) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	cout << separateurSections << "Vilains:" << endl;
	for (auto& v : vilains) {
		cout << separateurElements;
		v.changerCouleur(cout, 0);
		v.afficher(cout);
	}

	for (auto& h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto& v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	for (auto& p : peronnages) {
		cout << separateurElements;
		p->changerCouleur(cout, 0);
		p->afficher(cout);
	}
	cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	VilainHeros kefkaCrono(vilains[2], heros[0]);
	kefkaCrono.changerCouleur(cout,1);
	kefkaCrono.afficher(cout);
	#endif
	//}

	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeLieeHeros;
	for (auto& h : heros)
		listeLieeHeros.push_back(h);

	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut
	Iterateur<Heros> it = trouverParNom(listeLieeHeros, "Alucard");

	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	// en sachant qu'elle se trouve plus loin dans la liste.
	it.avancer();

	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	if (it != listeLieeHeros.end()) {
		Heros herosBidon("Héros Bidon", "Jeu Bidon", "Ennemi Bidon");
		listeLieeHeros.insert(it, herosBidon);
	}
    //TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	cout << separateurSections
		<< "Taille après insertion du héros bidon : "
		<< listeLieeHeros.size() << endl;

	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	it.reculer(); // Héros Bidon
	it.reculer(); // Alucard
	it.reculer(); // Naked Snake/John
	it.reculer(); // Mario
	Iterateur<Heros> itSuivantMario = listeLieeHeros.erase(it);
	cout << separateurSections
		<< "Héros suivant Mario après suppression :" << endl;
	if (itSuivantMario != listeLieeHeros.end()) {
		(*itSuivantMario).changerCouleur(cout, 0);
		(*itSuivantMario).afficher(cout);
	}
	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	cout << separateurSections
		<< "Taille après suppression de Mario : "
		<< listeLieeHeros.size() << endl;
	//TODO: Effacez le premier élément de la liste.
	if (!listeLieeHeros.estVide())
		listeLieeHeros.erase(listeLieeHeros.begin());

	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	// avec le héros Randi et n'a pas Mario.
	// Servez-vous des methodes begin et end de la liste...
	cout << separateurSections
		<< "Liste des héros (itérateur explicite) :" << endl;
	for (Iterateur<Heros> pos = listeLieeHeros.begin();
		pos != listeLieeHeros.end();
		pos.avancer()) {
		cout << separateurElements;
		(*pos).changerCouleur(cout, 0);
		(*pos).afficher(cout);
	}
	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	cout << separateurSections
		<< "Liste des héros (boucle for sur intervalle) :" << endl;
	for (Heros& h : listeLieeHeros) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	// 2.1 : Conteneur STL pour ordre alphabétique.
	// std::map maintient ses éléments triés automatiquement (arbre rouge-noir).
	map<string, Heros> herosAlpha;
	for (Heros& h : listeLieeHeros)
		herosAlpha.emplace(h.getNom(), h);

	cout << separateurSections
		<< "Héros en ordre alphabétique (std::map) :" << endl;
	for (auto& [nom, h] : herosAlpha) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	// 2.2 : Recherche dans std::map.
	// Complexité : O(log n).
	// Explication : std::map est un arbre rouge-noir équilibré;
	// la recherche divise l'espace de recherche par deux à chaque étape.
	const string nomRecherche = "Randi";
	auto itMap = herosAlpha.find(nomRecherche);
	if (itMap != herosAlpha.end()) {
		cout << separateurSections
			<< "Héros trouvé par nom (\"" << nomRecherche << "\") :" << endl;
		itMap->second.changerCouleur(cout, 0);
		itMap->second.afficher(cout);
	}

	// 2.3 : Comparaison des structures pour la recherche par nom.
	// ListeLiee : O(n) — parcours séquentiel obligatoire depuis la tête.
	// std::map  : O(log n) — arbre équilibré, recherche binaire.
	// Conclusion : std::map est nettement plus rapide pour rechercher par nom.
	//TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...
	}
