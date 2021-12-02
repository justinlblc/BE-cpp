#include "Bestiole.h"
#include "MultiBestiole.h"
#include "Comportement.h"
#include "Gregaire.h"
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

    this->setRandComp();
    this->setCouleur(this->comp->getCouleur());
}

MultiBestiole::MultiBestiole( const MultiBestiole & b, Gregaire * greg, Kamikaze * kami, Peureuse * peur, Prevoyante * prev):Bestiole(b){
    this->greg=greg;
    this->kami=kami;
    this->peur=peur;
    this->prev=prev;
}

void MultiBestiole::action(Milieu & monMilieu){
    cout<<age<<endl;
    if (this->age%100==0){
        this->setRandComp();
        this->setCouleur(this->comp->getCouleur());
    }
    comp->comp(*this, monMilieu);
    bouge( monMilieu.getWidth(), monMilieu.getHeight());
    age++;
}

void MultiBestiole::setRandComp(){
    int i = (int) std::rand()%(4-1)-1;
    switch(i){
        case 1:
            this->comp=greg;
        case 2:
            this->comp=kami;
        case 3:
            this->comp=peur;
        case 4:
            this->comp=prev;
    }
}

void MultiBestiole::setCouleur(T * coul){
    couleur[0]=coul[0];
    couleur[1]=coul[1];
    couleur[2]=coul[2];
}
