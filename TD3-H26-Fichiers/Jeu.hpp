// Jeu.hpp
// Definit la classe Jeu et ses operations.
#pragma once
#include <string>
#include <memory>
#include <utility>
#include "Liste.hpp"
#include "Concepteur.hpp"

class Jeu
{
public:
	// Constructeurs.
	Jeu() = default;
	Jeu(std::string titre, unsigned anneeSortie, std::string developpeur)
		: titre_(std::move(titre)), anneeSortie_(anneeSortie), developpeur_(std::move(developpeur)) {}

	const std::string& getTitre() const     { return titre_; }
	void setTitre(std::string titre)        { titre_ = std::move(titre); }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(std::string developpeur) { developpeur_ = std::move(developpeur); }

	// Acces aux concepteurs.
	Liste<Concepteur>& getConcepteurs() { return concepteurs_; }
	const Liste<Concepteur>& getConcepteurs() const { return concepteurs_; }

	// Ajoute un concepteur a ce jeu.
	void ajouterConcepteur(std::shared_ptr<Concepteur> concepteur)
	{
		concepteurs_.ajouterElements(std::move(concepteur));
	}

	// Trouver un concepteur selon un predicat (lambda).
	template <typename Predicate>
	Concepteur* trouverConcepteur(Predicate pred)
	{
		return concepteurs_.rechercherElements(pred);
	}

	// Version const.
	template <typename Predicate>
	const Concepteur* trouverConcepteur(Predicate pred) const
	{
		return concepteurs_.rechercherElements(pred);
	}


private:
	std::string titre_;
	unsigned anneeSortie_ = 0;
	std::string developpeur_;
	// Liste des concepteurs du jeu.
	Liste<Concepteur> concepteurs_;
};

using ListeJeux = Liste<Jeu>;
