#include "blocJoueur.h"
#include "blocTuile.h"
#include "tinyxml2.h"
#include "Partie.h"
#include "blocComposants.h"
#include "Controleur.h"




int main() {


	Site contenu[13];
	contenu[0]=Site::riviere;
	contenu[1] = Site::route;
	contenu[2] = Site::riviere;
	contenu[3] = Site::riviere;
	contenu[4] = Site::riviere;
	contenu[5] = Site::route;
	contenu[6] = Site::route;
	contenu[7] = Site::route;
	contenu[8] = Site::riviere;
	contenu[9] = Site::riviere;
	contenu[10] = Site::riviere;
	contenu[11] = Site::route;
	contenu[12] = Site::route;

	blocTuile::Tuile* t1 = new blocTuile::Tuile(contenu);
	blocTuile::Tuile* t2 = new blocTuile::Tuile(contenu);

	blocComposants::testFaceOuest(t1, t2);

	return 0;
}
// TEST CONTROLEUR ET SINGLETON PARTIE
	/*Site contenu[13];
	for (size_t i=0; i < 13; i++)
		contenu[i] = Site::route;

	blocTuile::Tuile t1(contenu);
	blocTuile::Tuile t2(contenu);

	blocComposants::testFaceOuest(&t1, &t2);*/

//blocTuile::Extensions *e1= new blocTuile::Extensions("test");
//blocJoueur::Joueur *j=new blocJoueur::Joueur("Pierre", Couleur::bleu);
//Partie::getInstance()->ajouterExtension(e1);
//Partie::getInstance()->ajouterJoueur(j);

////Partie::getInstance()->afficherExtensions();
////Partie::getInstance()->afficherJoueurs();
////Partie::getInstance()->afficherTuiles();

//Controleur c;
//c.creerPioche();
//c.piocherTuile();
//c.piocherTuile();
//std::cout << *Partie::getInstance()->getTuileEnJeu();
//c.ajouterTuilePlateau(0, 0);
//std::cout << c.getPlateau();


// TEST ROTATIONS

//int copie[1
// 
// ]; // copie d?truit ? la fin du bloc afin de sauvegarder les donn?es
//int contenu[13];
//int i;
//for (i = 0; i < 13; i++) {
//	contenu[i] = i;
//}
//for (i = 0; i < 13; i++) {
//	std::cout << contenu[i] << "/";
//}
//std::cout << "\n";
//for (i = 0; i < 12; i++) {
//	copie[i] = contenu[i];
//}
//
//for (i = 0; i < 12; i++) {
//	contenu[i] = copie[(i + 3) % 12];
//}
//for (i = 0; i < 12; i++) {
//	copie[i] = contenu[i];
//}
//
//for (i = 0; i < 12; i++) {
//	if (i < 3) contenu[i] = copie[i + 9];
//	else contenu[i] = copie[i - 3];
//}
//
//for (i = 0; i < 13; i++) {
//	std::cout << contenu[i] << "/";
//}
//std::cout << "\n";





	//Site contenu[13];
	//for (size_t i=0; i < 13; i++)
	//	contenu[i] = Site::route;
	//blocTuile::Tuile* t1=new blocTuile::Tuile(contenu);
	//blocTuile::Tuile* t2 = new blocTuile::Tuile(contenu);
	////std::cout<<blocComposants::testFaceOuest(t1, t2);
	//std::cout << t1;
	//blocComposants::Plateau p;
	//std::cout << p;
	//p.placerTuilePlateau(t1, 0, 0);

	//p.placerTuilePlateau(t1, 1, 1);
	//std::cout << p;