#include "Bestiole.h"
#include "MultiBestiole.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>

using namespace std;

MultiBestiole::MultiBestiole(Milieu & milieu, Gregaire * greg, Kamikaze * kami, Peureuse * peur, Prevoyante * prev):Bestiole(milieu, greg){
    //Propre à la classe MultiBestiole
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
    if (i==1){
        this->comp=greg;
    }
    else if (i==2){
        this->comp=kami;
    }
    else if (i==3){
        this->comp=peur;
    }
    else if (i==4){
        this->comp=prev;
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