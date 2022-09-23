#include "Partie.h"
#include "blocJoueur.h"
#include "blocTuile.h"
#include "blocComposants.h"

Partie* Partie::instance = nullptr;
Partie::~Partie() {
	for (auto it = joueurs.begin(); it != joueurs.end(); it++) {
		delete* it;
	}
	for (auto it = extensions.begin(); it != extensions.end(); it++) {
		delete* it;
	}
	libererInstance();
}

void Partie::ajouterExtension(blocTuile::Extensions* e) {
	if (e->getStatut()) {
		Partie::getInstance()->extensions.push_back(e);
		std::vector<blocTuile::Tuile*> tuiles_ext = e->getTuiles();
		for (size_t i = 0; i < tuiles_ext.size(); i++) {
			tuiles_en_jeu.push_back(tuiles_ext[i]);
		}
	}

}

void Partie::ajouterJoueur(blocJoueur::Joueur* j) {
	if (j) {
		if (Partie::getInstance()->joueurs.size() < NBJ) {
			Partie::getInstance()->joueurs.push_back(j);
			Partie::getInstance()->nb_joueur = Partie::getInstance()->joueurs.size();
		}
		else
			std::cout << "Nombre de joueurs max d?j? atteint \n";

	}
}

void Partie::remplirVecteurElementComplete(const blocComposants::Plateau p) {
	std::cout << "\n-------------MENU ELEMENT COMPLETE-----------------\n";
	bool continuer=0;
	int ligne;
	int colonne;
	do {
		try {
			std::cout << "\nChoissisez une ligne: ";
			std::cin >> ligne;
			std::cout << "\nChoissisez une colonne: ";
			std::cin >> colonne;

			if (ligne < 0 || colonne < 0) throw CarcasonneException("Indice plateau incorrect");
			if (ligne > X || colonne > Y) throw CarcasonneException("Indice plateau incorrect");
			if (p.getTuile(ligne, colonne) == nullptr) throw CarcasonneException("Il n'y a pas de tuile ? cet endroit");
			tuiles_complete.push_back(p.getTuile(ligne, colonne));

			std::cout << "\nVoulez vous continuer (1:oui/0:non): ";
			std::cin >> continuer;

		}
		catch (CarcasonneException exception) {
			std::cout << "\n" << exception.getInfo();

		}

	} while (continuer == 1);

	std::cout << "\n--------------------------------------------------------";


}


//void Partie::creerPioche() {
//	Partie::getInstance()->pioche = new blocComposants::Pioche;
//}

//void Partie::piocherTuile() { //pioche une tuile dans la pioche et la met en jeu
//	if (pioche) {
//		Partie::getInstance()->tuile = Partie::getInstance()->pioche->Piocher();
//		std::cout << "Tuile en jeu :" << Partie::getInstance()->tuile<<"\n";
//		return;
//	}
//	throw CarcasonneException("N'a pas pu mettre une tuile en jeu\n");
//}

//fonctions d'affichage des diff?rents vecteurs de partie

void Partie::afficherExtensions() const {
	if(instance){
		std::cout << "Liste des extensions dans la partie :\n";
		for (auto it = extensions.begin(); it != extensions.end(); it++) {
			std::cout << "- " << (*it)->getNom();

		}
		std::cout << "\n";
	}
	else {
		std::cout << "La partie n'existe pas encore\n";
	}
	

}

void Partie::afficherJoueurs() const {
	if (instance) {
		std::cout << "Liste des joueurs dans la partie :\n";
		for (auto it = joueurs.begin(); it != joueurs.end(); it++) {
			std::cout << "- " << (*it)->getNom() <<", couleur :"<<(*it)->getCouleur();

		}
		std::cout << "\n";

	}
	else {
		std::cout << "La partie n'existe pas encore\n";
	}


}

void Partie::afficherTuiles() const {
	if (instance) {
		int i = 0;
		std::cout << "Liste des tuiles dans la Partie:\n";
		for (unsigned int it = 0; it < tuiles_en_jeu.size(); it++) {
			i++;
			std::cout << "tuile " << i << ": " << *tuiles_en_jeu[it];
			std::cout << "\n";
		}
	}
	else {
		std::cout << "La partie n'existe pas encore\n";
	}


}