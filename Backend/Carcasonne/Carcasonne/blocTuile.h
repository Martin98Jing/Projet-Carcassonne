#pragma once
#include <iostream>
#include "blocJoueur.h"
#include <vector>
#include <stdlib.h>
#include "tinyxml2.h"

std::string toString(Site s);
std::ostream& operator<<(std::ostream& f, Site s);


namespace blocTuile{
	using namespace std;

	class Tuile {
		
        Site contenu[13];
		blocJoueur::Meeple* meeple;
		TypeMeeple type;
        int type_meeple;
		friend 	std::ostream& operator<<(std::ostream& f, Tuile s);


	public:
		Tuile(Site* tab) : meeple(nullptr), type_meeple(0) {
			//std::cout << "cree tuile :" << this << "\n";
			type = TypeMeeple::aucun;
			for (size_t i = 0; i < 13; i++) {
				contenu[i] = tab[i];
			}
			
		}
		const Site* getContenu() const { return contenu; }
		void afficherTuile() const;
		void rotationDroite();
		void rotationGauche();
        blocJoueur::Meeple* getMeeple()const {return meeple;}
		void setMeeple(blocJoueur::Meeple* m) { meeple = m; }
		void setTypeMeeple(TypeMeeple t) { type = t; }
		bool isSite(Site s);
        void setPosMeeple(int n){type_meeple=n;}
        int getPosMeeple() const{return type_meeple;}
        TypeMeeple getTypeMeeple() const{return type;}

		void retirerMeeple();
        Site getSite(size_t i) const {return contenu[i];}

	/*	Tuile* getNord() const { return nord; }
		Tuile* getEst() const { return est; }
		Tuile* getSud() const { return sud; }
		Tuile* getOuest() const { return ouest; }*/
	};
	std::ostream& operator<<(std::ostream& f, Tuile t);


	class Regles {
	private:
		int id;
		string description;
	public:
		Regles(int i,string desc):id(i),description(desc){}
		string getDescription() const { return description; }
		int getId() const { return id; }
	};

	class Extensions {
		bool jouable;
		string nom;
		vector<Tuile*> tuiles;
		vector<Regles*> regles;
		int initialiserFichier();
		void creationTuile(tinyxml2::XMLElement* ptr, size_t i);
		void creationRegle(tinyxml2::XMLElement* ptr,int id);

	public:
		~Extensions();
		Extensions(string nom);
		
		bool getStatut() const { return jouable; }
		auto getTuiles() const { return tuiles; }

		string getNom() const { return nom; }

		void ajouterTuile(Tuile* t) {
			if (t == nullptr) throw CarcasonneException("tuile non valide");
			tuiles.push_back(t);
			
		}
		void afficherExtensions() const;
		void afficherRegle() const;


	};
}
