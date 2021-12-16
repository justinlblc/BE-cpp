#include "Bestiole.h"
#include "MultiBestiole.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>

using namespace std;


//Constructeur
MultiBestiole::MultiBestiole(Milieu & milieu,  Gregaire * greg, Kamikaze * kami, Peureuse * peur, Prevoyante * prev):Bestiole(milieu, greg){
    //Propre à la classe MultiBestiole
    this->b1=b1;
    this->b2=b2;
    this->b3=b3;
    this->b4=b4;

    this->greg=greg;
    this->kami=kami;
    this->peur=peur;
    this->prev=prev;
    //cout<<"Avant random: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
    this->setRandComp(milieu);
    //cout<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
    //cout<<"Après random: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
    this->setCouleur(this->comp->getCouleur());
}

//Constructeur par copie
MultiBestiole::MultiBestiole( const MultiBestiole & b):Bestiole(b){
    this->greg=b.greg;
    this->kami=b.kami;
    this->peur=b.peur;
    this->prev=b.prev;
}

//Déplacement de la multibestiole à chaque pas de la simulation
void MultiBestiole::action(Milieu & monMilieu){
    //Nouveau comportement tous les 100 pas de simulation
    if (this->age%100==0 && this->age!=0){
        //cout<<"Avant: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
        cout<<"Age limite "<<this->getAgeLim()<< " âge réel "<<this->getAge()<<endl;
        //Nouveau comportement
        this->setRandComp(monMilieu);
        //cout<<"Après: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
        this->setCouleur(this->comp->getCouleur());
    }
    comp->comp(*this, monMilieu);
    bouge( monMilieu.getWidth(), monMilieu.getHeight());
    age++;
}

/*
Fonction qui renvoie un comportement aléatoire parmis ceux choisis par l'utilisateur

Input: Milieu
Output: None
*/
void MultiBestiole::setRandComp(Milieu & monMilieu){
    cout<<"Bug?"<<endl;
    int i = rand()% 4 +1;
    cout<<"Random comp: "<<i<<endl;

    if (i==1 && monMilieu.getb1()==true){
        //cout<<"Pas bug"<<endl;
        this->comp=greg;
    }
    else if (i==2 && monMilieu.getb2()==true){
        //cout<<"Pas bug"<<endl;
        this->comp=kami;
    }
    else if (i==3 && monMilieu.getb3()==true){
        //cout<<"Pas bug"<<endl;
        this->comp=peur;
    }
    else if (i==4 && monMilieu.getb4()==true){
        //cout<<"Pas bug"<<endl;
        this->comp=prev;
    }
    else{
        setRandComp(monMilieu);
    }       
}

/*
Changement de la couleur de la bestiole
Input: Couleur en question
Output: None
*/
void MultiBestiole::setCouleur(T * coul){
    couleur[0]=coul[0];
    couleur[1]=coul[1];
    couleur[2]=coul[2];
}

/*
Fonction permettant de savoir si la bestiole est une multibestiole
Input: None
Output: Booléen
*/
bool MultiBestiole::isMulti() const{
    return true;
}