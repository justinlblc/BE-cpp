#include "Bestiole.h"
#include "MultiBestiole.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>

using namespace std;

MultiBestiole::MultiBestiole(Milieu & milieu, bool b1, bool b2, bool b3, bool b4,  Gregaire * greg, Kamikaze * kami, Peureuse * peur, Prevoyante * prev):Bestiole(milieu, greg){
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
    this->setRandComp();
    //cout<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
    //cout<<"Après random: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
    this->setCouleur(this->comp->getCouleur());
}

MultiBestiole::MultiBestiole( const MultiBestiole & b):Bestiole(b){
    this->greg=b.greg;
    this->kami=b.kami;
    this->peur=b.peur;
    this->prev=b.prev;
}

void MultiBestiole::action(Milieu & monMilieu){
    if (this->age%100==0 && this->age!=0){
        //cout<<"Avant: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
        this->setRandComp();
        //cout<<"Après: "<<"Bestiole: "<< identite<<", âge: "<<this->age<<", Comportement:"<<this->comp->getId()<<endl;
        this->setCouleur(this->comp->getCouleur());
    }
    comp->comp(*this, monMilieu);
    bouge( monMilieu.getWidth(), monMilieu.getHeight());
    age++;
}

void MultiBestiole::setRandComp(){
    int i = rand()% 4 +1;
    //cout<<"Random comp: "<<i<<endl;
    if (i==1 && b1==true){
        this->comp=greg;
    }
    else if (i==2 && b2==true){
        this->comp=kami;
    }
    else if (i==3 && b3==true){
        this->comp=peur;
    }
    else if (i==4 && b4==true){
        this->comp=prev;
    }
    else{
        setRandComp();
    }       
}

void MultiBestiole::setCouleur(T * coul){
    couleur[0]=coul[0];
    couleur[1]=coul[1];
    couleur[2]=coul[2];
}

bool MultiBestiole::isMulti() const{
    return true;
}