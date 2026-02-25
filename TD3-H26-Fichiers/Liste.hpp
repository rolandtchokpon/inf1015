#pragma once
#include <iostream>
#include <memory>
#include <string>

// Conteneur générique qui partage ses éléments via std::shared_ptr.
template <typename T>
class Liste
{
public:
	// Construit une liste vide (capacité initiale 0).
	Liste() ;
	// Construit une liste vide avec une capacité initiale donnée.
	explicit Liste(unsigned capaciteAttendu);
	// Constructeur de copie (copie des shared_ptr).
	Liste(const Liste& autre);


	// Ajoute un élément à la fin de la liste (partage de propriété).
	void ajouterElements(std::shared_ptr<T> obj);

	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	// Retourne la capacité actuellement allouée.
	unsigned getCapacite() const  { return capacite_; }

	// Réalloue le stockage interne avec une nouvelle capacité.
	void augmenterCapacite(unsigned nouvelleCapacite);

	// Cherche le premier élément qui satisfait le prédicat; retourne nullptr sinon.
	template <typename Predicate>
	T* rechercherElements(Predicate pred);
	
	// Version const de la recherche.
	template <typename Predicate>
	const T* rechercherElements(Predicate pred) const;

	// Accès direct par indice (aucune validation des bornes).
	T& operator[](size_t i) { return *elements_[i]; }
	const T& operator[](size_t i) const { return *elements_[i]; }
	// Accès au shared_ptr stocké.
	std::shared_ptr<T>& getSharedPtr(size_t i) { return elements_[i]; }
	const std::shared_ptr<T>& getSharedPtr(size_t i) const { return elements_[i]; }

private:
	// Nombre d'éléments effectivement présents.
	unsigned nElements_;
	// Nombre de cases allouées dans le tableau.
	unsigned capacite_;
	// Tableau dynamique de pointeurs partagés vers les éléments.
	std::unique_ptr<std::shared_ptr<T>[]> elements_;
};
#include "Liste_impl.hpp"
