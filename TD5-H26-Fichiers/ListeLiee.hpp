#pragma once
#include "iterateur.hpp"
#include "gsl/gsl_assert"
template<typename T> class Iterateur;
template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.

	//TODO: La construction par défaut doit créer une liste vide valide.
	ListeLiee():
		tete_(nullptr), queue_(nullptr), taille_(0)
	{
	}
	~ListeLiee()
	{
		
		
		//TODO: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
		while (tete_ != nullptr) {
			Noeud<T>* teteActuelle = tete_;
			tete_ = tete_->suivant_;
			delete teteActuelle;
		}
		queue_  = nullptr;
		taille_ = 0;
	}

	bool estVide() const  { return taille_ == 0; }
	unsigned size() const { return taille_; }
	//NOTE: to_address (C++20) permet que ce même code fonctionne que vous utilisiez des pointeurs bruts ou intelligents (ça prend le pointeur brut associé au pointeur intelligent, s'il est intelligent).
	iterator begin()  { return {to_address(tete_)}; }
	iterator end()    { 
		if (queue_ != nullptr)
			return {to_address(queue_->suivant_)}; 
		return {nullptr};
	}

	// Ajoute à la fin de la liste.
	void push_back(const T& item)
	{
		//TODO: Vous devez créer un nouveau noeud en mémoire.
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		//TODO: Si la liste était vide, ce nouveau noeud est la tête et la queue;
		// autrement, ajustez la queue et pointeur(s) adjacent(s) en conséquence.
		if (estVide()) {
			tete_ = nouveauNoeud;
		}
		else {
			queue_->suivant_ = nouveauNoeud;//l'élément suivant de l'ancienne queue est le nouveauNoeud
			nouveauNoeud->precedent_ = queue_; //l'élément precedent du nouveauNoeud est l'ancienne queue
		}
		queue_ = nouveauNoeud;//officialise que la nouvelle queue est le nouveauNoeud
		taille_++;
	}

	// Insère avant la position de l'itérateur.
	iterator insert(iterator it, const T& item)
	{
		//NOTE: Pour simplifier, vous n'avez pas à supporter l'insertion à la fin (avant "past the end"),
		// ni l'insertion au début (avant la tête), dans cette méthode.
		//TODO:
		// 1. Créez un nouveau noeud initialisé avec item.
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		// 2. Modifiez les attributs suivant_ et precedent_ du nouveau noeud
		//    afin que le nouveau noeud soit lié au noeud précédent et suivant
		//    à l'endroit où il est inséré selon notre itérateur.
		Noeud<T>* apres = it.position_;
		Expects(apres != nullptr);
		Noeud<T>* avant = apres->precedent_;
		nouveauNoeud->suivant_ = apres;
		nouveauNoeud->precedent_ = avant;
		// 3. Modifiez l'attribut precedent_ du noeud après la position d'insertion
		//    (l'itérateur) afin qu'il pointe vers le noeud créé.
		apres->precedent_ = nouveauNoeud;
		// 4. Modifiez l'attribut suivant_ du noeud avant la position d'insertion
		//    (précédent de l'itérateur) afin qu'il point vers le noeud créé.
		Expects(avant != nullptr);
		avant->suivant_ = nouveauNoeud;
		
		// 5. Incrémentez la taille de la liste.
		taille_++;
			// 6. Retournez un nouvel itérateur initialisé au nouveau noeud.
		
		return iterator(nouveauNoeud);
	}

	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(iterator it)
	{
		//TODO: Enlever l'élément à la position de l'itérateur.
		//  1. Le pointeur vers le Noeud à effacer est celui dans l'itérateur.
		Noeud<T>* aEffacer = it.position_;
		Noeud<T>* avant    = aEffacer->precedent_;
		Noeud<T>* apres    = aEffacer->suivant_;
		//  2. Modifiez l'attribut suivant_ du noeud précédent pour que celui-ci
		//     pointe vers le noeud suivant la position de l'itérateur (voir 1.).
		if (avant != nullptr) {
			avant->suivant_ = apres;
		}
		else {
			tete_ = apres;
		}
		//  3. Modifiez l'attribut precedent_ du noeud suivant la position de
		//     l'itérateur pour que celui-ci pointe vers le noeud précédent
		//     de la position de l'itérateur (voir 1.).
		if (apres != nullptr) {
			apres->precedent_ = avant;
		}
		else {
			queue_ = avant;
		}
		//  4. Désallouez le Noeud à effacer (voir 1.).
		delete aEffacer;
		//  5. Décrémentez la taille de la liste
		taille_--;
		if (taille_ == 0) {
			queue_ = nullptr;
		}
		//  6. Retournez un itérateur vers le suivant du Noeud effacé.
		return iterator(apres);
		//TODO: On veut supporter d'enlever le premier élément de la liste,
		//  donc en 2. il se peut qu'il n'y ait pas de précédent et alors c'est
		//  la tête de liste qu'il faut ajuster.
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).
	}

private:
	gsl::owner<Noeud<T>*> tete_;  //NOTE: Vous pouvez changer le type si vous voulez.
	Noeud<T>* queue_;
	unsigned taille_;
};
