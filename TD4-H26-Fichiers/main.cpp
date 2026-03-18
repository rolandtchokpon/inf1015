#include <fstream>
#include <vector>
#include "bibliotheque_cours.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
using namespace std;

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

template <class T>
concept Dereferencable = requires (T&& t) { *std::forward<T>(t); };

// Surcharge quand c'est un pointeur
template <Dereferencable T> 
decltype(auto) as_ref(T&& t)
{
	return *std::forward<T>(t);
}

// Surcharge moins contrainte (donc quand ce n'est pas un pointeur)
template <class T>
T&& as_ref(T&& t) {
	return std::forward<T>(t);
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

	// Ouverture des fichiers binaires
	ifstream fichierHeros("heros.bin", ios::binary);
	ifstream fichierVilains("vilains.bin", ios::binary);
	fichierHeros.exceptions(ios::failbit);
	fichierVilains.exceptions(ios::failbit);

	//TODO: Votre code pour le main commence ici
	vector<Heros>       heros;
	vector<Vilain>      vilains;
	vector<Personnage*> personnages;

	UInt16 nHeros = lireUint16(fichierHeros);
	heros.reserve(nHeros);
	for (UInt16 i = 0; i < nHeros; i++) {
		string nom = lireString(fichierHeros);
		string parution = lireString(fichierHeros);
		string ennemi = lireString(fichierHeros);

		UInt8 nAllies = lireUint8(fichierHeros);
		vector<string> allies;
		allies.reserve(nAllies);
		for (UInt8 j = 0; j < nAllies; j++)
			allies.push_back(lireString(fichierHeros));

		heros.push_back(Heros(nom, parution, ennemi, allies));
	}

	UInt16 nVilains = lireUint16(fichierVilains);
	vilains.reserve(nVilains);
	for (UInt16 i = 0; i < nVilains; i++) {
		string nom = lireString(fichierVilains);
		string parution = lireString(fichierVilains);
		string objectif = lireString(fichierVilains);
		vilains.push_back(Vilain(nom, parution, objectif));
	}

	auto afficherVecteur = [&](auto& vecteur, const string& palette) {
		for (auto& p : vecteur) {
			as_ref(p).changerCouleur(palette);
			as_ref(p).afficher(cout);
			cout << trait << "\n";
		}
		};

	afficherVecteur(heros, "heros");
	afficherVecteur(vilains, "vilain");

	// La ligne suivante ne compile pas (copie protected) - laissée en commentaire intentionnellement.
	// Personnage p = heros[0];

	for (auto& h : heros)
		personnages.push_back(&h);
	for (auto& v : vilains)
		personnages.push_back(&v);

	afficherVecteur(personnages, "");

	int indexVilain = 0;
	int indexHeros = 0;
	for (int i = 0; i < (int)heros.size(); i++) {
		bool vilainEstValide = true;
		for (int k = 0; k < (int)vilains.size(); k++) {
			if (vilains[k].getNom() == heros[i].getEnnemi() && k == indexVilain) {
				vilainEstValide = false;
				break;
			}
		}
		if (vilainEstValide) {
			indexHeros = i;
			break;
		}
	}

	VilainHeros fusion(vilains[indexVilain], heros[indexHeros]);
	fusion.changerCouleur("vilainHeros");
	fusion.afficher(cout);
	cout << trait << "\n";

	personnages.push_back(&fusion);
	afficherVecteur(personnages, "");
}
