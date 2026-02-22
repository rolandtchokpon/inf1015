#pragma once
#include <iostream>
#include <memory>
#include <string>

//TODO: Rentdre la liste générique.
template <typename T>
class Liste
{
public:
	//TODO: Constructeurs et surcharges d'opérateurs
	Liste() ;
	explicit Liste(unsigned capaciteAttendu);


	//TODO: Méthode pour ajouter un élément à la liste
	void ajouterElements(std::unique_ptr<T> obj);

	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned getCapacite() const  { return capacite_; }

	//TODO: Méthode pour changer la capacité de la liste
	void augmenterCapacite(unsigned nouvelleCapacite);

	//TODO: Méthode pour trouver un élément selon un critère (lambda).
	template <typename Predicate>
	T* rechercherElements(Predicate pred);
	
	template <typename Predicate>
	const T* rechercherElements(Predicate pred) const;

	//Operator pour les indices
	T& operator[](size_t i) { return *elements_[i]; }
	const T& operator[](size_t i) const { return *elements_[i]; }

private:
	unsigned nElements_;
	unsigned capacite_;
	//TODO: Attribut contenant les éléments de la liste.
	std::unique_ptr<std::unique_ptr<T>[]> elements_;
};
#include "Liste_impl.hpp"