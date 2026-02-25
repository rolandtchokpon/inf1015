// Concepteur.hpp
// Definit la classe Concepteur et ses acces aux donnees.
#pragma once
#include <string>
#include <utility>

class Concepteur
{
public:
	// Constructeurs.
	Concepteur() = default;
	Concepteur(std::string nom, int anneeNaissance, std::string pays)
		: nom_(std::move(nom)), anneeNaissance_(anneeNaissance), pays_(std::move(pays)) {}

	const std::string& getNom() const     { return nom_; }
	void setNom(std::string nom)          { nom_ = std::move(nom); }
	int getAnneeNaissance() const         { return anneeNaissance_; }
	void setAnneeNaissance(int annee)     { anneeNaissance_ = annee; }
	const std::string& getPays() const    { return pays_; }
	void setPays(std::string pays)        { pays_ = std::move(pays); }

private:
	std::string nom_;
	int anneeNaissance_ = 0;
	std::string pays_;
};
