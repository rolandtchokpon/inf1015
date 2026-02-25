// lectureFichierJeux.cpp
// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include <cstdint>
#include <type_traits>
#include "cppitertools/range.hpp"
#include "Liste.hpp"
using namespace std;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

#pragma region "Fonctions de lecture de base"
// Fonction générique: accepte uniquement les types trivialement copiables.
template <typename T, typename = enable_if_t<is_trivially_copyable_v<T>>>
T lireType(istream& fichier)
{
	T valeur{};
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireType<UInt16>(fichier));
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

shared_ptr<Concepteur> lireConcepteur(ListeJeux& listeJeux, istream& fichier)
{
	string nom              = lireString(fichier);
	unsigned anneeNaissance = lireType<UInt16>(fichier);
	string pays             = lireString(fichier);

	// Cherche un concepteur existant; sinon, cree un nouveau.
	auto concepteur = chercherConcepteur(listeJeux, nom);
	if (concepteur == nullptr)
		concepteur = make_shared<Concepteur>(nom, anneeNaissance, pays);

	cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return concepteur;
}

Jeu* lireJeu(istream& fichier, ListeJeux& listeJeux)
{
	string titre          = lireString(fichier);
	unsigned anneeSortie  = lireType<UInt16>(fichier);
	string developpeur    = lireString(fichier);
	unsigned nConcepteurs = lireType<UInt8>(fichier);
	// Cree un jeu et attache ses concepteurs.
	auto jeu = make_shared<Jeu>(titre, anneeSortie, developpeur);
	for (unsigned int i = 0; i < nConcepteurs; i++)
		jeu->ajouterConcepteur(lireConcepteur(listeJeux, fichier));
	listeJeux.ajouterElements(jeu);

	cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return jeu.get();
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	//string exempleTypeInvalide = lireType<string>(fichier); // Ne compile pas: string n'est pas trivially_copyable
	int nElements = lireType<UInt16>(fichier);
	ListeJeux listeJeux;
	//Creer une liste de jeux
	for ([[maybe_unused]] int i : iter::range(nElements))
		lireJeu(fichier, listeJeux);

	//Retourner la liste de jeu
	return listeJeux;
}
