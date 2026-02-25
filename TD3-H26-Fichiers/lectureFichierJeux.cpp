// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include <cstdint>
#include "cppitertools/range.hpp"
#include "Liste.hpp"
using namespace std;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

#pragma region "Fonctions de lecture de base"
//TODO: Remplacer lireUint8 et lireUint16 par une seule fonction générique qui permet les deux, mais permettre uniquement des types qui sont is_trivially_copyable_v (un trait de type).
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
#pragma endregion

shared_ptr<Concepteur> chercherConcepteur(ListeJeux& listeJeux, const string& nom)
{
	for (unsigned i = 0; i < listeJeux.size(); i++) {
		auto& concepteurs = listeJeux[i].getConcepteurs();
		for (unsigned j = 0; j < concepteurs.size(); j++) {
			if (concepteurs[j].getNom() == nom)
				return concepteurs.getSharedPtr(j);
		}
	}
	return {};
}

shared_ptr<Concepteur> lireConcepteur(ListeJeux& lj, istream& f)
{
	string nom              = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays             = lireString(f);

	// Cherche un concepteur existant; sinon, cree un nouveau.
	auto concepteur = chercherConcepteur(lj, nom);
	if (!concepteur)
		concepteur = make_shared<Concepteur>(nom, anneeNaissance, pays);

	cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return concepteur;
}

Jeu* lireJeu(istream& f, ListeJeux& lj)
{
	string titre          = lireString(f);
	unsigned anneeSortie  = lireUint16(f);
	string developpeur    = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	// Cree un jeu et attache ses concepteurs.
	auto jeu = make_shared<Jeu>(titre, anneeSortie, developpeur);
	for (unsigned int i = 0; i < nConcepteurs; i++)
		jeu->ajouterConcepteur(lireConcepteur(lj, f));
	lj.ajouterElements(jeu);

	cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return jeu.get();
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	ListeJeux listeJeux;
	//Creer une liste de jeux
	for ([[maybe_unused]] int i : iter::range(nElements))
		lireJeu(f, listeJeux);

	//Retourner la liste de jeu
	return listeJeux;
}
