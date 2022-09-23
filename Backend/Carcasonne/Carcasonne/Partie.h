#pragma once
#include "blocJoueur.h"
#include "blocTuile.h"
#include <vector>
#include "blocComposants.h"
#include "Controleur.h"

#define NBJ 6

/* Travail ? faire sur la classe
* compl?ter le destructeur pour lib?rer la m?moire

ajouter plateau  et pioche
nb de joueurs = taille du vecteur joueurs + 4 max
*/



class Partie {
private :

	Partie() :nb_joueur(0), tour(0),tuile(nullptr) {}
	~Partie();
	Partie& operator=(const Partie&)=delete;
	Partie(const Partie&)=delete;

	int nb_joueur;
	int tour;

	blocTuile::Tuile* tuile;

	std::vector<blocJoueur::Joueur*> joueurs;
	std::vector<blocTuile::Tuile*> tuiles_en_jeu;
	std::vector<blocTuile::Extensions*>extensions;
	std::vector<blocTuile::Tuile*> tuiles_rivieres;
	std::vector<blocTuile::Tuile*> tuiles_complete;

	static Partie* instance;

	friend class Controleur;
public:
	static Partie* getInstance() {
		if (instance == nullptr) {
			instance = new Partie;
		}
		return instance ;
	}
	static void libererInstance() {
		delete instance;
		instance = nullptr;
	}

	int getTour() const { return Partie::getInstance()->tour; }
	auto* getTuilesRiviere() const { return &Partie::getInstance()->tuiles_rivieres; }
	blocTuile::Tuile* getTuileEnJeu() const { return Partie::getInstance()->tuile; }
	std::vector<blocTuile::Tuile*> getTuilesEnJeu() const { return Partie::getInstance()->tuiles_en_jeu; }
	
	void prochainJoueur() {
		Partie::getInstance()->tour++;
		if(Partie::getInstance()->tour== Partie::getInstance()->nb_joueur) 
			Partie::getInstance()->tour=0;

	}

	void ajouterExtension(blocTuile::Extensions* e);
	void ajouterJoueur(blocJoueur::Joueur* j);

	void afficherTuiles() const;
	void afficherExtensions() const;
	void afficherJoueurs() const;
    void ajouterTuileComplete(blocTuile::Tuile* t){
        if(t!=nullptr)
            tuiles_complete.push_back(t);

    }

	blocJoueur::Joueur* getJoueurEnCours() const { return joueurs[tour]; }

	blocTuile::Tuile getTuile(size_t i) const {
		if (i > tuiles_en_jeu.size())
			throw CarcasonneException("Erreur indice");
		return *tuiles_en_jeu[i];
	}
	



	void setTuileEnJeu(blocTuile::Tuile* t) { tuile = t; }
	void remplirVecteurElementComplete(const blocComposants::Plateau p);
    void viderComplete(){tuiles_complete.clear();}
	int getNbJoueur() const { return joueurs.size(); }
	blocJoueur::Joueur* getJoueur(int i) const{ return joueurs[i]; }
	auto getTuilesCompleteBegin() const { return tuiles_complete.begin(); }
	auto getTuilesCompleteEnd() const { return tuiles_complete.end(); }

};
