#include "blocTuile.h"
#include "blocJoueur.h"
#include "tinyxml2.h"
#include <string>


std::string toString(Site s) {
	switch (s) {
	case Site::abbaye: return "abbaye";
	case Site::route: return "route";
	case Site::ville: return "ville";
	case Site::riviere: return "riviere";
	case Site::prairie: return "prairie";
	case Site::village: return "village";
	case Site::source: return "source";
	case Site::lac: return "lac";
    case Site::cathedrale: return "cathedrale";
    case Site::pont: return "pont";
    case Site::auberge: return "auberge";
    case Site::blason: return "blason";
    case Site::jardin: return "jardin";
    case Site::carrefour: return "carrefour";
	default: throw CarcasonneException("Site inconnue");		
	}
}

Site toSite(std::string s) {
	using namespace std;
	if (s=="abbaye")return Site::abbaye;
	if (s == "ville")return Site::ville;
	if (s == "route")return Site::route;
	if (s == "riviere")return Site::riviere;
	if (s == "prairie") return Site::prairie;
	if (s == "village") return Site::village;
	if (s == "source") return Site::source;
	if (s == "lac") return Site::source;
    if(s=="cathedrale")return Site::cathedrale;
    if(s=="pont" )return Site::pont;
    if(s=="auberge" )return Site::auberge;
    if(s=="blason" )return Site::blason;
    if(s=="jardin" )return Site::jardin;
    if(s=="carrefour") return Site::carrefour;

	std::cout << "echec\n";
	//throw CarcasonneException("Site inconnue");
}
std::ostream& operator<<(std::ostream& f, Site s) {
	f << toString(s);
	return f;

}
namespace blocTuile {
	//fonctions et méthodes pour la tuile
	void Tuile::afficherTuile() const {
//		if (this == nullptr) {
//			std::cout << "Pointeur Null\n";
//			return;
//		}
		for (size_t i = 0; i < 13; i++) {
			std::cout << contenu[i] << ";";
		}
		std::cout << "\n";
	}
	std::ostream& operator<<(std::ostream& f, Tuile t) {
		f << "Tuile :";
		for (size_t i = 0; i < 13; i++) {

			f << t.contenu[i]<<"/";
		}
		if (t.meeple != nullptr)
            f << " type meeple:" << t.type<<" position: "<<t.type_meeple << " adresse: " << t.meeple ;
		f << "\n";
		return f;
	}
    void Tuile::rotationGauche() {
		Site copie[13]; // copie détruit à la fin du bloc afin de sauvegarder les données
		int i;
        for (i = 0; i < 13; i++) {
			copie[i] = contenu[i];
		}
        for (i = 1; i < 13; i++) {  //a cause du 0 que l'on ignore à un moment on passe de +3 à +4
            //std::cout<<"\ncase "<<i<<" devient"<<(i + 3) % 13<<"ou"<<(i + 4) % 13;
            if(i>=10){
                contenu[i]=copie[(i+4)%13];
                 //std::cout<<"\ncase "<<i<<" devient"<<(i + 4) % 13;
            }
            else{
                contenu[i] = copie[(i + 3) % 13];
                //std::cout<<"\ncase "<<i<<" devient"<<(i + 3) % 13;
               }

		}


	}
    void Tuile::rotationDroite() {
		Site copie[13]; // copie détruit à la fin du bloc afin de sauvegarder les données
		int i;
        //std::cout<<"-------------------droite\n";
        for (i = 0; i < 13; i++) {
			copie[i] = contenu[i];
		}
        for (i = 1; i < 13; i++) {  //meme principe
            //std::cout<<"\ncase "<<i<<" devient"<<(i + 9) % 12;
            if(i<=3)
                contenu[i] = copie[(i + 9) % 13];
            else
                contenu[i] = copie[(i + 10) % 13];

		}


	}

	bool Tuile::isSite(Site s) {
		for (size_t i = 0; i < 13; i++) {
			if (contenu[i] == s)
				return true;
		}
		return false;
	}


	//fonctions et méthodes pour les extensions
	Extensions::~Extensions() {
		for (auto it = tuiles.begin(); it != tuiles.end(); it++) {
			delete *it;
		}
		for (auto it = regles.begin(); it != regles.end(); it++) { 
			delete* it;
		}
	}

	void Extensions::creationTuile(tinyxml2::XMLElement* ptr,size_t i) {//va créer i fois la tuile à l'adresse ptr dans le fichier xml
		//std::cout << "On cree la tuile " << i << "\n";
		Site tableau[13];
		std::string resultat;
		std::string indice;
		for (int i = 0; i < 13; i++) {
			indice = "case" + std::to_string(i);
			resultat = ptr->Attribute(indice.c_str());
			//std:cout << indice << ":" << resultat<<"\n";
			tableau[i] = toSite(resultat);
		}

		/*for (size_t i = 0; i < 13; i++) {
			cout << tableau[i] << "\n";
		}*/
		Tuile* nouvelle_tuile = new Tuile(tableau);
		this->ajouterTuile(nouvelle_tuile);
	}

	void Extensions::creationRegle(tinyxml2::XMLElement* ptr,int id) {
		//std::cout << "\ncreer regle";
		string description = ptr->Attribute("description");
		//std::cout << "\ndescription : "<<description;
		Regles* nouvelle_regle = new Regles(id, description);
		regles.push_back(nouvelle_regle);
	}

	int Extensions::initialiserFichier() {
		using namespace std;
		int nb_tuile;
		int max_tuile = 15;

		string f = nom + ".xml";
		
		tinyxml2::XMLDocument doc;

		tinyxml2::XMLError eResult = doc.LoadFile(f.c_str());
		if (eResult != tinyxml2::XML_SUCCESS) {
			cout << "Erreur lors de l'initialisation de l'extension " << nom << "\n";
			return -1;
		}
		tinyxml2::XMLNode* root = doc.FirstChildElement("root");//se place sur le noeud root dans le fichier
		if (root == nullptr) {
			cout << "Erreur dans la lecture du doc\n";
			return -1;
		}
		tinyxml2::XMLElement* ptr_tuiles = root->FirstChildElement("tuiles");
		tinyxml2::XMLElement* ptr_regles = root->FirstChildElement("regles");
		
		cout << ptr_tuiles<<"\n";
		cout << "Pointeurs sur les regles : " << ptr_regles << "\n";
		//root = doc.FirstChildElement("tuiles");
		if (ptr_tuiles) {
			tinyxml2::XMLElement* ptr = ptr_tuiles->FirstChildElement("tuile");//se place sur le premier élément tuile du fichier xml
			while (ptr) { //tant que l'on a des tuiles
				//cout << ptr;
				ptr->QueryIntAttribute("exemplaire", &nb_tuile);//transforme la valeur d'exemplaire en entier
				if (nb_tuile<0 || nb_tuile>max_tuile) {//dans le cas où lit un nombre abberant -> on s'arrête éviter boucles infines dans le pg
					std::cout << "Erreur lors de la lecture du fichier \n";
					return -1;
				}
				//cout << nb_tuile<<"\n";
				for (size_t i = 1; i <= nb_tuile; i++) {
					creationTuile(ptr, i);
				}
				ptr = ptr->NextSiblingElement();//passe à la tuile suivante
			}
		}
		if (ptr_regles) {
			tinyxml2::XMLElement* ptr_regle = ptr_regles->FirstChildElement("regle");
			int id_regle = 0;
			while (ptr_regle) {
				id_regle++;
				creationRegle(ptr_regle, id_regle);
				ptr_regle = ptr_regle->NextSiblingElement();
			}
		}
		return 0;
		

	}

	//constructuer
	Extensions::Extensions(string n) :nom(n) {
		int resultat=this->initialiserFichier();//lit les données dans le fichier xml de l'extensions
		if (resultat != 0) {
			std::cout << "L'extention " << nom << "à eu souci lors de l'intialisation, elle ne sera pas jouable\n";
			jouable = 0;
		}
		jouable = 1;
	}
	void Extensions::afficherExtensions() const{
		int i = 0;
		for (unsigned int it = 0;it<tuiles.size();it++) {
			i++;
			std::cout << "tuile " << i << ": " << *tuiles[it];
			std::cout << "\n";

		}
		std::cout << "fin affichage\n";
	}

	void Extensions::afficherRegle() const {
		std::cout << "\n------------------------\nAffichage des regles de l'extensions " << nom << "\n";
		for (auto it = regles.begin(); it != regles.end(); it++) {
			std::cout << "\n" << (*it)->getDescription();

		}
	}
	bool IsMeepleSpeciale(TypeMeeple t) {
		if (t == TypeMeeple::paysan) return 1;
		return 0;

	}
	void Tuile::retirerMeeple() {
		if (meeple != nullptr) {
			if (!IsMeepleSpeciale(type)) {
				meeple->setTypeMeeple(TypeMeeple::aucun);
				type_meeple = 0;
				type = TypeMeeple::aucun;
				meeple = nullptr;
			}

		}
		else {
			std::cout << "\n aucun meeple sur la tuile: " << this;
		}

	}



}


	//std::string CouleurCase(Site s) {
	//	switch (s) {
	//	case Site::abbaye: return "yelllow";
	//	case Site::ville: return "brown";
	//	case Site::route: return "grey";
	//	case Site::riviere: return "blue";
	//	case Site::village: return "orange";
	//	case Site::prairie: return "green";
	//	}
	//}

	//void AffichageTuile() const
	//{
	//	QPainter painter(T);
	//	QPen pen(Qt::black);
	//	painter.setPen(pen);

	//	QPainterPath t1;
	//	t1.moveTo(10, 10);
	//	t1.lineTo(10, 110);
	//	t1.lineTo(110, 110);
	//	painter.setBrush(QColor(CouleurCase(contenu[1])));
	//	painter.drawPath(t1);

	//	QPainterPath t2;
	//	t2.moveTo(10, 10);
	//	t2.lineTo(110, 10);
	//	t2.lineTo(110, 110);
	//	painter.setBrush(QColor(CouleurCase(contenu[2])));
	//	painter.drawPath(t2);

	//	QRect r3(110, 10, 100, 100);
	//	pen.setColor(QColor(CouleurCase(contenu[3])));
	//	painter.drawRect(r3);
	//	painter.fillRect(r3, pen.brush());

	//	QPainterPath t4;
	//	t4.moveTo(210, 10);
	//	t4.lineTo(310, 10);
	//	t4.lineTo(210, 110);
	//	painter.setBrush(QColor(CouleurCase(contenu[4])));
	//	painter.drawPath(t4);

	//	QPainterPath t5;
	//	t5.moveTo(210, 110);
	//	t5.lineTo(310, 10);
	//	t5.lineTo(310, 110);
	//	painter.setBrush(QColor(CouleurCase(contenu[5])));
	//	painter.drawPath(t5);

	//	QRect r6(210, 110, 100, 100);
	//	pen.setColor(QColor(CouleurCase(contenu[6])));
	//	painter.drawRect(r6);
	//	painter.fillRect(r6, pen.brush());

	//	QPainterPath t7;
	//	t7.moveTo(210, 210);
	//	t7.lineTo(310, 210);
	//	t7.lineTo(310, 310);
	//	painter.setBrush(QColor(CouleurCase(contenu[7])));
	//	painter.drawPath(t7);

	//	QPainterPath t8;
	//	t8.moveTo(210, 210);
	//	t8.lineTo(210, 310);
	//	t8.lineTo(310, 310);
	//	painter.setBrush(QColor(CouleurCase(contenu[8])));
	//	painter.drawPath(t8);

	//	QRect r9(110, 210, 100, 100);
	//	pen.setColor(QColor(CouleurCase(contenu[9])));
	//	painter.drawRect(r9);
	//	painter.fillRect(r9, pen.brush());

	//	QPainterPath t10;
	//	t10.moveTo(110, 210);
	//	t10.lineTo(10, 310);
	//	t10.lineTo(110, 310);
	//	painter.setBrush(QColor(CouleurCase(contenu[10])));
	//	painter.drawPath(t10);

	//	QPainterPath t11;
	//	t11.moveTo(110, 210);
	//	t11.lineTo(10, 310);
	//	t11.lineTo(10, 210);
	//	painter.setBrush(QColor(CouleurCase(contenu[11])));
	//	painter.drawPath(t11);

	//	QRect r12(10, 110, 100, 100);
	//	pen.setColor(QColor(CouleurCase(contenu[12])));
	//	painter.drawRect(r12);
	//	painter.fillRect(r12, pen.brush());

	//	QRect r0(110, 110, 100, 100);
	//	pen.setColor(QColor(CouleurCase(contenu[0])));
	//	painter.drawRect(r0);
	//	painter.fillRect(r0, pen.brush());
	//}
