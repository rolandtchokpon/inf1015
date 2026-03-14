#pragma once
#include <string>
#include <iostream>

using namespace std;

class Affichable {
	public:
		virtual ~Affichable() = default;
		virtual void afficher(ostream& os) = 0;
		virtual void changerCouleur(const string& palette) = 0;
};