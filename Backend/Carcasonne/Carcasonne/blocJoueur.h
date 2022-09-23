#pragma once
#include <iostream>


#define NBMEEPLE 8

enum class Couleur { bleu, jaune, rouge, vert,noir,gris};
enum class TypeMeeple {aucun,brigand, chevalier,abbe,paysan};
enum class Site {riviere, village,prairie,route, ville,abbaye,source,lac,jardin,cathedrale,blason,auberge,pont,carrefour};


std::string toString(Couleur c);
std::string toString(TypeMeeple t);

TypeMeeple toTypeMeeple(Site s);


std::ostream& operator<<(std::ostream& f, Couleur c);
std::ostream& operator<<(std::ostream& f, TypeMeeple t);

class CarcasonneException { // classe pour g?rer les potentielles exceptions
public:
	CarcasonneException(const std::string& i) :info(i) {}
	std::string getInfo() const { return info; }
private:
	std::string info;
};

namespace blocJoueur { // g?rer les classes en lien direct avec les joueurs + manque encore l'h?ritage
	using namespace std;
	class Meeple;

	class Joueur {
		string nom;
		Couleur couleur;
		int points;
		Meeple** meeple;
	public:
		Joueur(string n,Couleur c);
		~Joueur() { delete[] meeple; }
		/*Joueur(const Joueur&) = delete;
		const Joueur& operator=(const Joueur&) = delete;*/
		string getNom() const { return nom; }
		Couleur getCouleur() const { return couleur; }
		int getPoints() const { return points; }
		void setPoitns(int n) { points += n; }
		Meeple* getMeepleDispo() const;
        int MeepleRestants() const;
	};


	class Meeple {
		Joueur* proprietaire;
		TypeMeeple type;
	public:
		~Meeple();
		Meeple(Joueur* j) :proprietaire(j),type(TypeMeeple::aucun){}
		Meeple(const Meeple&) = delete;
		const Meeple& operator=(const Meeple&) = delete;
		Joueur& Proprietaire() const { return *proprietaire; }
        Joueur* Proprietaire_ptr() const { return proprietaire; }

		TypeMeeple getType() const { return type; }

		void setTypeMeeple(TypeMeeple t) { type = t; }

		void retourReserve();


	};	
}
