#pragma once
#include "blocTuile.h"
#include <vector>
#define X 5
#define Y 5

namespace blocComposants {
	using namespace std;
	class Pioche {
	private:
		vector<blocTuile::Tuile*> tuiles;
		//Pioche& operator=(const Pioche&) = delete;
		//Pioche(const Pioche&) = delete;
		friend ostream& operator<<(ostream& f, Pioche p);

		
	public:
		explicit Pioche();
		explicit Pioche(std::vector<blocTuile::Tuile*> vec);
		bool estVide() const { return tuiles.empty(); }
		size_t getNbTuiles() const { return tuiles.size(); }
		blocTuile::Tuile* Piocher();
		auto getTuilesPioche() const { return tuiles; }
};
	ostream& operator<<(ostream& f, Pioche p);

	class Plateau {
	private:
		blocTuile::Tuile* tuiles_plateau[X][Y] ;
		bool plateau_vide; //permet de placer la premi?re tuile au d?but

		friend std::ostream& operator<<(std::ostream& f, Plateau p);
	public:
		Plateau():plateau_vide(1) { //initialise un plateau vide
			for (size_t i = 0; i < X; i++) {
				for (size_t j = 0; j < Y; j++)
					tuiles_plateau[i][j] = nullptr;
			}
		}
		void demanderPlacement(blocTuile::Tuile* t,int* ligne, int* colonne);
		bool plateauComplet() const;
        bool placerTuilePlateau(blocTuile::Tuile* t,int x,int y);//place une tuile dans le tableau
		bool placementCorrectTuile(blocTuile::Tuile* t, int ligne, int colonne); //v?rifie le placement d'une tuile
		auto getMatricePlateau() const { return tuiles_plateau; }
		blocTuile::Tuile* getTuile(int ligne, int colonne) const { return tuiles_plateau[ligne][colonne]; }
        bool tuilePresente(blocTuile::Tuile* t) const;
        void retirerTuile(blocTuile::Tuile* t,int *x,int *y);


	};
	std::ostream& operator<<(std::ostream& f, Plateau p);

	//fonction externes utilsier pour v?rifier le placement de la tuile
	bool testFaceNord(blocTuile::Tuile* t, blocTuile::Tuile* N);
	bool testFaceSud(blocTuile::Tuile* t, blocTuile::Tuile* S);
	bool testFaceEst(blocTuile::Tuile* t, blocTuile::Tuile* E);
	bool testFaceOuest(blocTuile::Tuile* t, blocTuile::Tuile* O);

}
