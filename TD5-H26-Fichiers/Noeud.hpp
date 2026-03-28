#pragma once
#include <gsl/pointers>
template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO: Constructeur(s).
	Noeud(const T& donnee):
		donnee_(donnee)
	{};

private:
	//TODO: Attributs d'un noeud.
	Noeud* suivant_ = finListe;	
	Noeud* precedent_ = finListe;
	T donnee_; 

	inline static constexpr Noeud* finListe = nullptr;
};
