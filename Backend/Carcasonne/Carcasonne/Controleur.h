#pragma once
#include "blocComposants.h"
#include "Partie.h"
#include "blocTuile.h"
#include "blocJoueur.h"

class Controleur;

class Strategie { //classe abstraite qui contient la m?thode regle que l'on va substituer par polymorphisme
public:
	virtual void regle(Controleur* c) = 0;
};

class Controleur { //context
private:
	blocComposants::Pioche* pioche;
	blocComposants::Plateau plateau;
	Strategie* regle_en_cours;
    int pos_meeple;
public:
    Controleur() :pioche(nullptr), regle_en_cours(nullptr),pos_meeple(0){
	
	}
	~Controleur() {
		delete pioche;
	}

	void creerPioche(); //initalise la pioche et met toutes les tuiles en jeu dedans
	void piocherTuile(); //pioche une tuile de la pioche et la met en jeu(attibut tuile dans le singleton partie)
    bool ajouterTuilePlateau(int x,int y); //prend la tuile en jeu et essaye de la mettre sur le plateau
    void retirerTuilePlateau(blocTuile::Tuile* t,int *x,int *y){plateau.retirerTuile(t,x,y);}
	void finDeTour();


	blocComposants::Plateau getPlateau() const { return plateau; }
	blocComposants::Pioche* getPioche() const { return pioche; }

	void execute() { regle_en_cours->regle(this); } //permet d'?x?cuter une r?gle
	void setRegle(Strategie* strat) { regle_en_cours = strat; } //permet de mettre en place une r?gle
	void jouerPartie(); //m?thode lanc? apr?s initialisation de partie, va jouer la partie en affectuant et ex?cutant les diff?rentes r?gles
						//utilisation de strat?gie permet de modeler plus facilement la partie que si on utilisait de simple m?thodes

    void setPosMeeple(int n){pos_meeple=n;}
    int getPosMeeple() const {return pos_meeple;}


};

// ensemble des r?gles
class ReglePoserMeeple : public Strategie { // classes fille de strat?gie, scontienent le code des r?gles en elle m?mes
public:
	void regle(Controleur* c) override;
};


class ReglePoserTuileRiviere : public Strategie { // classes fille de strat?gie, scontienent le code des r?gles en elle m?mes
public:
	void regle(Controleur* c) override;
};

class RegleElementComplete: public Strategie { // classes fille de strat?gie, scontienent le code des r?gles en elle m?mes
public:
	void regle(Controleur* c) override;
};







