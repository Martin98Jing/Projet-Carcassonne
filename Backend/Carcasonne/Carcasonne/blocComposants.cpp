#include "blocComposants.h"
#include "Partie.h"

namespace blocComposants {

	Pioche::Pioche() { //le constructeur r?cup?re les tuiles en jeu de partie et les met dans la pioche
		auto vec_tuiles_en_jeu = Partie::getInstance()->getTuilesEnJeu();
		std::vector<blocTuile::Tuile*> tuiles_rivieres;
		for (auto it = vec_tuiles_en_jeu.begin(); it != vec_tuiles_en_jeu.end(); it++) {
			if (!(*it)->isSite(Site::riviere) && !(*it)->isSite(Site::source) && !(*it)->isSite(Site::lac))
				tuiles.push_back((*it));
			if ((*it)->isSite(Site::riviere) || (*it)->isSite(Site::source) || (*it)->isSite(Site::lac))
				tuiles_rivieres.push_back((*it));
				
		}
		if (!tuiles_rivieres.empty())
		std::vector<blocTuile::Tuile*> *var = Partie::getInstance()->getTuilesRiviere();
		for (auto it = tuiles_rivieres.begin(); it != tuiles_rivieres.end(); it++) {
			Partie::getInstance()->getTuilesRiviere()->push_back((*it));
			
		}
	}
	Pioche::Pioche(std::vector<blocTuile::Tuile*> vec) {
		for (auto it = vec.begin(); it != vec.end(); it++) {
			//std::cout << "\ntest affichage: " << (*it);
			tuiles.push_back((*it));
		}
		
		/*for (auto it = tuiles.begin(); it != tuiles.end(); it++) {
			std::cout <<"\n" << **it;
		}*/
	}

	ostream& operator<<(ostream& f, Pioche p) {
		std::cout << "Tuiles dans la pioche: \n";
		for (auto it = p.tuiles.begin(); it != p.tuiles.end(); it++) {
			std::cout << "-" << *(*it) << "\n";
			
		}
		return f;

	}

	blocTuile::Tuile* Pioche::Piocher() {
		if (this->estVide())
			throw CarcasonneException("Pioche Vide");
		if (Partie::getInstance()->getTuileEnJeu() == nullptr) {
			unsigned int x = rand() % tuiles.size();
			blocTuile::Tuile* t = tuiles[x];
			tuiles.erase(tuiles.begin() + x);
			return t;
		}
		else
			throw CarcasonneException("Une tuile est dej? en jeu, vous ne pouvez pas piocher tout de suite\n");
		

	}
	bool Plateau::plateauComplet() const {
		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < Y; j++) {
				if (tuiles_plateau[i][j] == nullptr)
					return false;
			}
		}
		return true;
	}

	void Plateau::demanderPlacement(blocTuile::Tuile* t, int* ligne, int* colonne) {
		if (plateauComplet()) {
			std::cout << "\n Le plateau est complet?, la partie est donc finie";
			//MAJ attribut fin de partie; pour finir la partie -> rajouter une m?thode pour finir la partie
		}
		bool placement_correct = 0;
		do {
			try { //l'utilisateur rentre son choix, ? impl?menter avec l'interfae
				std::cout << "\nChoissisez une ligne: ";
				std::cin >> *ligne;
				std::cout << "\nChoissisez une colonne: ";
				std::cin >> *colonne;

				if (*ligne < 0 || *colonne < 0) throw CarcasonneException("Indice plateau incorrect");
				if (*ligne > X || *colonne > Y) throw CarcasonneException("Indice plateau incorrect");
				placement_correct = placementCorrectTuile(t, *ligne, *colonne);


			}
			catch (CarcasonneException exception) {
				std::cout << "L'emplacement choisi n'est pas valide: " << exception.getInfo();
			}

		} while (placement_correct==0);

	}
	bool Plateau::placementCorrectTuile(blocTuile::Tuile* t, int ligne, int colonne) {
        std::cout<<"\n----------------------------------------------------------------\n"<<*t<<"\n";
        if (tuiles_plateau[ligne][colonne] != nullptr){
            std::cout<<"\ntest"<<tuiles_plateau[ligne][colonne];
			throw CarcasonneException("\nUne tuile est deja placee a cette position");
        }
		blocTuile::Tuile* N=nullptr;
		blocTuile::Tuile* E=nullptr;
		blocTuile::Tuile* S=nullptr;
		blocTuile::Tuile* O=nullptr;

		//if (ligne < 0 || colonne < 0) throw CarcasonneException("Indice plateau incorrect");
		//if (ligne > X || colonne > Y) throw CarcasonneException("Indice plateau incorrect");

		if (ligne != 0)
			N = tuiles_plateau[ligne-1][colonne];
		if (colonne != 0)
			O = tuiles_plateau[ligne][colonne-1];
		if (ligne != X - 1)
			S = tuiles_plateau[ligne+1][colonne];
		if (colonne != Y - 1)
			E = tuiles_plateau[ligne][colonne+1];

        std::cout << "\n";
        std::cout << "test affichage S " <<S << "\n";
        std::cout << "test affichage N " << N << "\n";
        std::cout << "test affichage O " << O << "\n";
        std::cout << "test affichage E " <<E << "\n";
		if (!plateau_vide && N==nullptr && S==nullptr && O==nullptr && E==nullptr)
			throw CarcasonneException("Il faut au moins une tuile adjacente");

        if (testFaceEst(t, E) && testFaceNord(t, N) && testFaceOuest(t, O) && testFaceSud(t, S))
			return 1;
		else
			throw CarcasonneException("Le placement choisie n'est pas valide");
		 
	}

    bool Plateau::placerTuilePlateau(blocTuile::Tuile* t,int x,int y) {
        //int ligne, colonne;
		std::cout << "On place la tuile " << t << "\n";
        //demanderPlacement(t,&ligne, &colonne);
        //tuiles_plateau[ligne][colonne] = t;
        if (placementCorrectTuile(t, x, y)) {
            tuiles_plateau[x][y] = t;
            plateau_vide = 0;
            return 1;
        }
        else {
            std::cout << "Le placement de la tuile n'est pas valide";
            return 0;
        }
	}

	bool testFaceNord(blocTuile::Tuile* t, blocTuile::Tuile* N) {
        std::cout<<"\n verif nord"<<t<<" ";
        if(N)
             std::cout<<*N<<"\n";
		if (t == nullptr) throw CarcasonneException("Pointeurs sont nuls");
		if (N == nullptr) return 1;
		const Site* t_tab = t->getContenu();
		const Site* N_tab = N->getContenu();
        if((t_tab[9]==Site::ville && N_tab[3]==Site::blason )||(t_tab[3]==Site::blason && N_tab[9]==Site::ville))
            return 1;
        if(t_tab[3]!=N_tab[9])
            return 0;

        //unsigned int i = 8;

//		for (size_t indice = 2; indice < 5; indice++) {
//            std::cout << "indice =" << indice << " indice +i=" << indice + i << "\n";

//			if (t_tab[indice] != N_tab[indice + i]) return 0;
//			i=i-2;
//		}
		return 1;
	}
	bool testFaceSud(blocTuile::Tuile* t, blocTuile::Tuile* S) {
        std::cout<<"\n verif sud"<<t<<" ";
        if(S)
           std::cout <<*S<<"\n";
		if (t == nullptr) throw CarcasonneException("Pointeurs sont nuls");
		if (S == nullptr) return 1;

		const Site* t_tab = t->getContenu();
		const Site* S_tab = S->getContenu();
         if((t_tab[9]==Site::ville && S_tab[3]==Site::blason )||(t_tab[3]==Site::blason && S_tab[9]==Site::ville))
             return 1;

        if(t_tab[9]!=S_tab[3])
            return 0;
        //unsigned int i = 4;

//		for (size_t indice = 8; indice < 11; indice++) {
//			std::cout << "indice =" << indice << " indice - i=" << indice - i << "\n";
//			if (t_tab[indice] != S_tab[indice - i]) return 0;
//			i = i +2;
//		}
		return 1;
	}
	bool testFaceEst(blocTuile::Tuile* t, blocTuile::Tuile* E) {
        std::cout<<"\n verif est"<<t<<" ";
        if(E)
           std::cout <<*E<<"\n";

		if (t == nullptr) throw CarcasonneException("Pointeurs sont nuls");
		if (E == nullptr) return 1;

		unsigned int i = 0;
		const Site* t_tab = t->getContenu();
		const Site* E_tab = E->getContenu();
        if((t_tab[12]==Site::ville && E_tab[6]==Site::blason )||(t_tab[12]==Site::blason && E_tab[6]==Site::ville)) //blason considere comme une ville
            return 1;
        if(t_tab[6]!=E_tab[12])
            return 0;
//		for (size_t indice = 5; indice < 8; indice++) {
//            std::cout << "\nindice =" << indice << " (12-i)%12=" << ((12 - i) % 12)+1 << "\n";

//			if (t_tab[indice] !=E_tab[((12 - i) % 12) + 1]) return 0;
//			i = i+1;
//		}
		return 1;

	}
	bool testFaceOuest(blocTuile::Tuile* t, blocTuile::Tuile* O) {
        std::cout<<"\n verif ouest"<<t<<" ";
        if(O)
            std::cout<<*O<<"\n";

        if (t == nullptr) throw CarcasonneException("Pointeurs sont nuls");
		if (O== nullptr) return 1;

        //unsigned int i = 0;

		const Site* t_tab = t->getContenu();
		const Site* O_tab = O->getContenu();
        if((t_tab[12]==Site::ville && O_tab[6]==Site::blason )||(t_tab[12]==Site::blason && O_tab[6]==Site::ville)) //blason considere comme une ville
            return 1;
        if(t_tab[12]!=O_tab[6])
            return 0;
		//std::cout << "\n";
//		for (size_t indice = 5;indice<8;indice++) {
//            std::cout << "indice =" << indice << " (12-i)%12=" << ((12 - i) % 12) + 1 << "//contenu"<<O_tab[indice]<<" "<<t_tab[((12 - i) % 12) + 1]<<"\n";
//			if (O_tab[indice] != t_tab[((12 - i) % 12) + 1]) return 0;
//			i++;
		
//		}
		return 1;
	}
	std::ostream& operator<<(std::ostream& f, Plateau p) {

		for (size_t i = 0; i < X; i++) {
			for (size_t j = 0; j < Y; j++) {
				if (p.tuiles_plateau[i][j] == nullptr)
					f << "Emplacement " << i << " " << j << " " << "nul\n";
				else
					f << "Emplacement " << i << " " << j << " " <<": "<<p.tuiles_plateau[i][j] << *p.tuiles_plateau[i][j];

			}
		}
		return f;
	}

    bool Plateau::tuilePresente(blocTuile::Tuile* t) const{
        for (size_t i = 0; i < X; i++) {
            for (size_t j = 0; j < Y; j++) {
                if(t==tuiles_plateau[i][j])
                    return 1;

            }
        }
        return 0;

    }

    void Plateau::retirerTuile(blocTuile::Tuile* t,int *x,int *y){
        for (size_t i = 0; i < X; i++) {
            for (size_t j = 0; j < Y; j++) {
                if(t==tuiles_plateau[i][j]){
                    *x=i;
                    *y=j;
                    tuiles_plateau[i][j]=nullptr;
                    std::cout<<"test remise ? z?ro"<< tuiles_plateau[i][j]<<"\n";
                }
           }
        }
        for (size_t i = 0; i < X; i++) {
            for (size_t j = 0; j < Y; j++) {
                if(tuiles_plateau[i][j]!=nullptr){
                    plateau_vide=0;
                    return;
                }
           }
        }
        plateau_vide=1;


    }


}
