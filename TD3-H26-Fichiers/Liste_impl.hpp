#pragma once 
#include <iostream>
#include <memory>
#include "Liste.hpp"
using namespace std;

template <typename T>
Liste<T>::Liste() : capacite_(0), nElements_(0), elements_(nullptr){};

template <typename T>
Liste<T>::Liste(unsigned capaciteAttendu) :
	capacite_(capaciteAttendu), nElements_(0),
	elements_(capacite_ ? make_unique<unique_ptr <T>[]>(capacite_) : nullptr)
{}

template <typename T>
void Liste<T>::ajouterElements(unique_ptr<T> obj) {
	if (!obj) return; // arrêt de la fcontion si aucun pointeur

	if (nElements_ >= capacite_) {
		augmenterCapacite(capacite_ == 0 ? 1 : capacite_ * 2);
	}

	elements_[nElements_] = move(obj);
	++nElements_;

	//cout << "Element bien ajouté!" << endl;
	//cout << "Nombre delements : " << nElements_;
}

template <typename T>
template <typename Predicate>
T* Liste<T>::rechercherElements(Predicate pred) {
	for (unsigned i = 0; i < nElements_; i++) {
		if (elements_[i] && pred(*elements_[i])) {
			return elements_[i].get();
		}
	}
	return nullptr;
}
template <typename T>
template <typename Predicate>
const T* Liste<T>::rechercherElements(Predicate pred) const {
	for (unsigned i = 0; i < nElements_; i++) {
		if (elements_[i] && pred(*elements_[i])) {
			return elements_[i].get();
		}
	}
	return nullptr;
}

template <typename T>
void Liste<T>::augmenterCapacite(unsigned nouvelleCapacite) {

	auto nouvelleListe = make_unique<unique_ptr<T>[]>(nouvelleCapacite);

	for (unsigned i = 0; i < nElements_; i++) {
		nouvelleListe[i] = move(elements_[i]);
	}
	elements_ = move(nouvelleListe);
	capacite_ = nouvelleCapacite;
}
