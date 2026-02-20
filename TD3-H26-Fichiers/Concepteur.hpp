#pragma once
#include <string>

class Concepteur
{
public:
	//TODO: Un constructeur par défaut et un constructeur paramétré.

	const std::string& getNom() const     { return nom_; }
	void setNom(std::string nom)          { nom_ = move(nom); }
	int getAnneeNaissance() const         { return anneeNaissance_; }
	void setAnneeNaissance(int annee)     { anneeNaissance_ = annee; }
	const std::string& getPays() const    { return pays_; }
	void setPays(std::string pays)        { pays_ = move(pays); }

private:
	std::string nom_;
	int anneeNaissance_;
	std::string pays_;
};
