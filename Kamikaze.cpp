#include "Kamikaze.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Kamikaze::Kamikaze(void){
    couleur = new T[3];
    couleur[0]=39;
    couleur[1]=118;
    couleur[2]=32;
    return;
};

void Kamikaze::comp(Bestiole& b, Milieu & monMilieu){
    std::vector<Bestiole> *liste = monMilieu.getListeBestioles();
    int k = liste->size();
    if (k>1){
        int l = 0;
        double distFinale = (double) monMilieu.getWidth();
        for (int i =0; i<k;i++){
            double dist = std::sqrt((b.getX()-(*liste)[i].getX())*(b.getX()-(*liste)[i].getX())+(b.getY()-(*liste)[i].getY())*(b.getY()-(*liste)[i].getY()));
            if (dist<distFinale && dist!=0){
                distFinale=dist;
                l =i;
            }
        }
        //calcul de la nouvelle orientation
        //disjonction de cas
        Bestiole *cible = &(*liste)[l];
        double orientation = std::acos((cible->getX()-b.getX())/distFinale);
        if (cible->getY()<b.getY()){
            orientation = -orientation;
        }
        b.setOrientation(orientation);
    }
}

T *Kamikaze::getCouleur(){
    return this->couleur;
}

