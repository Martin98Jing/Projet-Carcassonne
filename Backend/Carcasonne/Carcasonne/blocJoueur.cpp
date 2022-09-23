#include "blocJoueur.h"

std::string toString(Couleur c) {
	switch (c) {
	case Couleur::rouge: return "rouge";
	case Couleur::bleu: return "bleu";
	case Couleur::vert: return "vert";
	case Couleur::jaune: return "jaune";
	case Couleur::gris: return "gris";
	case Couleur::noir: return "noir";

	default: throw CarcasonneException("Couleur inconnue");
	}
}

std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }

std::string toString(TypeMeeple t) {
	switch (t) {
	case TypeMeeple::aucun: return "aucun";
	case TypeMeeple::brigand: return "brigand";
	case TypeMeeple::chevalier: return "chevalier";
	case TypeMeeple::abbe: return "abbe";
    case TypeMeeple::paysan: return "paysan";
    default: throw CarcasonneException("M?tier de Meeple inconnu");

	}
}

TypeMeeple toTypeMeeple(Site s) {
	switch (s) {
	case Site::route: return TypeMeeple::brigand;
	case Site::abbaye: return TypeMeeple::abbe;
	case Site::ville: return TypeMeeple::chevalier;
	case Site::prairie: return TypeMeeple::paysan;

//	default: throw CarcasonneException("\n Site inconnu");
    default: return TypeMeeple::aucun;
	}
}


std::ostream& operator<<(std::ostream& f, TypeMeeple t) { f << toString(t); return f; }

namespace blocJoueur {
	Joueur::Joueur(string n, Couleur c) :nom(n), couleur(c),points(0) {
		meeple = new Meeple* [8];
		for (int i = 0; i < 8; i++) {
			meeple[i] = new Meeple(this);
		}
	}
	Meeple* Joueur::getMeepleDispo() const {
		for (size_t i = 0; i < NBMEEPLE; i++) {
			if (meeple[i]->getType() == TypeMeeple::aucun)
				return meeple[i];
		}
		return nullptr;
	}

    int Joueur::MeepleRestants() const{
        int retour=0;
        for(size_t i=0;i<NBMEEPLE;i++){
            if(meeple[i]->getType()==TypeMeeple::aucun)
                retour++;
        }
        return retour;
    }

	


}

