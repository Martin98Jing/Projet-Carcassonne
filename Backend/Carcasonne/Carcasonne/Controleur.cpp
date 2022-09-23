#include "Controleur.h"
#include "blocComposants.h"

void Controleur::creerPioche() {
	pioche = new blocComposants::Pioche;
}

void Controleur::finDeTour() {
	Partie::getInstance()->tuile = nullptr;
	Partie::getInstance()->prochainJoueur();
}

void Controleur::piocherTuile() { //pioche une tuile dans la pioche et la met en jeu
	if (pioche) {
		Partie::getInstance()->tuile = this->pioche->Piocher();
		std::cout << "Tuile en jeu :" << Partie::getInstance()->tuile << "\n";
		return;
	}
	throw CarcasonneException("N'a pas pu mettre une tuile en jeu (Pioche vide ou pas initialis?e)\n");
}

bool Controleur::ajouterTuilePlateau(int x,int y) {//permet d'ajouter la tuile en jeu dans le plateau
	if (Partie::getInstance()->tuile) {
		std::cout << "------------------------------------------------------------------\nOn place la tuile " << *Partie::getInstance()->getTuileEnJeu() << "\n";

        return plateau.placerTuilePlateau(Partie::getInstance()->tuile,x,y);
//		bool placement_meeple = 0;
//		std::cout << "\nVoulez vous placer un meeple sur votre tuile ? ";
//		std::cin >> placement_meeple;
//		if (placement_meeple) {
//			ReglePoserMeeple regle;
//			setRegle(&regle);
//			try {
//				execute();
//			}
//			catch (CarcasonneException exception) {}
//			return;
//		}
    }
    else{
		throw CarcasonneException("Il n'y a pas de tuile en jeu");
        return 0;
    }

}

//definition des r?gles de la classe Strat?gie
bool SiteValide(const Site* tab, int position) { //lister les sites o? il est interdit de poser un meeple
    if (tab[position] == Site::lac || tab[position] == Site::riviere || tab[position] == Site::source|| tab[position]==Site::jardin ||tab[position]==Site::auberge)
		return 1;
	return 0;
}


void ReglePoserMeeple::regle(Controleur* c) {
    blocJoueur::Joueur* j = Partie::getInstance()->getJoueurEnCours();
    blocJoueur::Meeple* m = j->getMeepleDispo();
    //std::cout << "Adresse du meeple "<<m<<"\n";

    if (m == nullptr) {
        std::cout << "\nLe joueur " << j->getNom() << " n'a pas de meeple disponible";
        throw CarcasonneException("\nPlus de meeple dans la r?serve");
    }
    else {
        int position;
        Partie::getInstance()->getTuileEnJeu()->setMeeple(m);
        const Site* tab = Partie::getInstance()->getTuileEnJeu()->getContenu();

//		std::cout << "\nSaisissez la position du meeple: ";
//		do {
//			std::cin >> position;

//		} while (position < 0 || position>12 ||SiteValide(tab,position));
        position=c->getPosMeeple();
        std::cout<<"\ntest de la position poser meeple"<<position<<" et affichage site"<<tab[position];
        if(SiteValide(tab,position))
            throw CarcasonneException("Le site choisi n'est pas valide");

        TypeMeeple metier = toTypeMeeple(tab[position]);
        std::cout<<"\nAffichage metier meeple"<<toString(metier);
        m->setTypeMeeple(metier);
        Partie::getInstance()->getTuileEnJeu()->setTypeMeeple(metier);
        Partie::getInstance()->getTuileEnJeu()->setPosMeeple(position);


    }
}


//void ReglePoserMeeple::regle(Controleur* c) {
//	blocJoueur::Joueur* j = Partie::getInstance()->getJoueurEnCours();
//	blocJoueur::Meeple* m = j->getMeepleDispo();
//    //std::cout << "Adresse du meeple "<<m<<"\n";

//	if (m == nullptr) {
//		std::cout << "\nLe joueur " << j->getNom() << " n'a pas de meeple disponible";
//		throw CarcasonneException("\nPlus de meeple dans la r?serve");
//	}
//	else {
//        int position;
//		Partie::getInstance()->getTuileEnJeu()->setMeeple(m);
//		const Site* tab = Partie::getInstance()->getTuileEnJeu()->getContenu();

////		std::cout << "\nSaisissez la position du meeple: ";
////		do {
////			std::cin >> position;

////		} while (position < 0 || position>12 ||SiteValide(tab,position));
//        position=c->getPosMeeple();
//        std::cout<<"\ntest de la position poser meeple"<<position;
//        if(SiteValide(tab,position))
//            throw CarcasonneException("Le site choisi n'est pas valide");

//        TypeMeeple metier = toTypeMeeple(tab[position]);
//        if(metier==TypeMeeple::aucun){
//            throw CarcasonneException("Vous ne pouvez pas placer de meeple ? cet endroit");

//        }
//        else{
//        m->setTypeMeeple(metier);
//        Partie::getInstance()->getTuileEnJeu()->setTypeMeeple(metier);
//        Partie::getInstance()->getTuileEnJeu()->setPosMeeple(position);
//        }


//	}
//}




//void  ReglePoserTuileRiviere::regle(Controleur* c) {
//	auto* vec_tuiles_rivieres = Partie::getInstance()->getTuilesRiviere();
//	blocTuile::Tuile* source = nullptr;
//	blocTuile::Tuile* lac = nullptr;
//	int id_lac=0;
//	int id_source=0;
//	int i = 0;
//	for (auto it = vec_tuiles_rivieres->begin(); it != vec_tuiles_rivieres->end(); it++) {
//		if ((*it)->isSite(Site::lac)) {
//			lac = (*it);
//			id_lac = i;
//		}
		
//		if ((*it)->isSite(Site::riviere)) {
//			source=(*it);
//			id_source=i;

//		}
//		i++;
//	}

//	std::cout << "\nretirer les tuiles lac et source\n";
//	vec_tuiles_rivieres->erase(vec_tuiles_rivieres->begin() + id_lac);
//	vec_tuiles_rivieres->erase(vec_tuiles_rivieres->begin() + (id_source-1));

//	blocComposants::Pioche* pioche_riviere=new blocComposants::Pioche (*vec_tuiles_rivieres);
//	std::cout << "affichage des tuiles restantes dans la pioche riviere\n";
//	/*for (auto it = vec_tuiles_rivieres->begin(); it != vec_tuiles_rivieres->end(); it++) {
//		std::cout << **it;
//	}*/
//	std::cout << *pioche_riviere;


//	Partie::getInstance()->setTuileEnJeu(source);
//	std::cout << "\ntuile source: " << *Partie::getInstance()->getTuileEnJeu();
//	//recup les indices placement de la tuile (en cliquant sur l'interface)
//	c->ajouterTuilePlateau();
//	c->finDeTour();
//	bool abandon = 0;
//	while (!abandon && !pioche_riviere->estVide()) {
//		try {
//			Partie::getInstance()->setTuileEnJeu(pioche_riviere->Piocher());
//			c->ajouterTuilePlateau();
//			c->finDeTour();
//		}
//		catch (CarcasonneException c) {
//			std::cout << c.getInfo();
//		}
//	}
//	Partie::getInstance()->setTuileEnJeu(lac);
//	c->ajouterTuilePlateau();
//	c->finDeTour();
//	delete pioche_riviere;
//}

void RegleElementComplete::regle(Controleur* c) {
    //Partie::getInstance()->remplirVecteurElementComplete(c->getPlateau());
    //int nb_points=0;
	std::cout << "\n---------------MENU ATTRIBUTION DES POINTS---------------\n";
//	for (size_t i = 0; i < Partie::getInstance()->getNbJoueur(); i++) {
//		std::cout << "\n Combien de points pour le joueur " << Partie::getInstance()->getJoueur(i)->getNom()<<": ";
//		std::cin >> nb_points;
//	}
	std::cout << "\n------------------------------------------------------------";
	for (auto it = Partie::getInstance()->getTuilesCompleteBegin(); it != Partie::getInstance()->getTuilesCompleteEnd(); it++) {
		(*it)->retirerMeeple();
	}
    Partie::getInstance()->viderComplete();


}
