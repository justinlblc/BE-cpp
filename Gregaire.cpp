#include "Gregaire.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;


Gregaire::Gregaire(void){
    couleur = new T[3];
    couleur[0]=248;
    couleur[1]=22;
    couleur[2]=15;
    return;
};

void Gregaire::comp(Bestiole& b, Milieu & monMilieu){
    double orientation;
    int nbVoisin = monMilieu.nbVoisins(b);
    if (nbVoisin>=1){
        int k = monMilieu.getListeBestioles()->size();
        std::vector<std::shared_ptr<Bestiole>> *liste = monMilieu.getListeBestioles();
        for (int i =0;i<k;i++ ){
            if ( !(b == *(*liste)[i]) && b.jeTeVois(*(*liste)[i])){
                orientation+=(*liste)[i]->getOrientation();
            }
        }
        if (b.getOrientation()!=orientation){
            b.setOrientation(orientation/nbVoisin);
        }
    }
    cout<<"Gregaire"<<endl;
}

T *Gregaire::getCouleur(){
    return this->couleur;
}

char Gregaire::getId(){
    return ('G');
}
//destructeur
