#include "Peureuse.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int Peureuse::tolerance=2;

Peureuse::Peureuse(void){
    couleur = new T[3];
    couleur[0]=82;
    couleur[1]=176;
    couleur[2]=173;
    return;
};

void Peureuse::comp(Bestiole& b, Milieu & monMilieu){
    int nbVoisin = monMilieu.nbVoisins(b);
    if (nbVoisin>=tolerance && !(b.getFuis())){
        vitesse=b.getVitesse();
        b.setOrientation(M_PI-b.getOrientation());
        b.setVitesse(b.getVMAX());
        b.setFuis(true);

    }
    else if (nbVoisin<tolerance && b.getFuis()){
        b.setFuis(false);
        b.setVitesse(this->vitesse);
    }
}

T *Peureuse::getCouleur(){
    return this->couleur;
}
