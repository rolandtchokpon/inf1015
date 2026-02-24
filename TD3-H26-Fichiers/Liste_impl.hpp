#pragma once
#include <iostream>
#include <memory>
#include "Liste.hpp"
using namespace std;

template <typename T>
// Constructeur par defaut: liste vide sans allocation initiale.
Liste<T>::Liste() : capacite_(0), nElements_(0), elements_(nullptr){};

template <typename T>
// Constructeur avec capacite initiale; alloue seulement si capacite > 0.
Liste<T>::Liste(unsigned capaciteAttendu) :
	capacite_(capaciteAttendu), nElements_(0),
	elements_(capacite_ ? make_unique<shared_ptr<T>[]>(capacite_) : nullptr)
{}

template <typename T>
void Liste<T>::ajouterElements(shared_ptr<T> obj) {
	// Ignore les pointeurs nuls pour conserver des elements valides.
	if (!obj) return;

	// Agrandit la capacite au besoin (doublement, ou 1 si la liste est vide).
	if (nElements_ >= capacite_) {
		augmenterCapacite(capacite_ == 0 ? 1 : capacite_ * 2);
	}

	// Deplace le shared_ptr a la fin pour eviter un +1 puis -1 inutile.
	elements_[nElements_] = move(obj);
	++nElements_;
}

template <typename T>
template <typename Predicate>
T* Liste<T>::rechercherElements(Predicate pred) {
	// Parcourt la liste et retourne le premier element qui satisfait le predicat.
	for (unsigned i = 0; i < nElements_; i++) {
		if (elements_[i] && pred(*elements_[i])) {
			return elements_[i].get();
		}
	}
	// Aucun element correspondant.
	return nullptr;
}

template <typename T>
template <typename Predicate>
const T* Liste<T>::rechercherElements(Predicate pred) const {
	// Meme logique que la version non-const, mais pour une liste const.
	for (unsigned i = 0; i < nElements_; i++) {
		if (elements_[i] && pred(*elements_[i])) {
			return elements_[i].get();
		}
	}
	// Aucun element correspondant.
	return nullptr;
}

template <typename T>
void Liste<T>::augmenterCapacite(unsigned nouvelleCapacite) {
	// Alloue un nouveau tableau, puis transfere les elements existants.
	auto nouvelleListe = make_unique<shared_ptr<T>[]>(nouvelleCapacite);

	for (unsigned i = 0; i < nElements_; i++) {
		nouvelleListe[i] = elements_[i];
	}

	// Remplace l'ancien stockage et met a jour la capacite.
	elements_ = move(nouvelleListe);
	capacite_ = nouvelleCapacite;
}
