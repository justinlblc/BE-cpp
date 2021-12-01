#include "Kamikaze.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Kamikaze::Kamikaze(void){
    return;
};

void Kamikaze::comp(Bestiole& b, Milieu & monMilieu){
    std::vector<Bestiole> *liste = monMilieu.getListeBestioles();
    int k = liste->size();
    double distFinale = monMilieu.getWidth();
    Bestiole *cible;
    for (int i =0; i<k;i++){
        double dist = std::sqrt(b.getX()-(*liste)[i].getX())*(b.getX()-(*liste)[i].getX())+(b.getY()-(*liste)[i].getY())*(b.getY()-(*liste)[i].getY()));
        if (dist<distFinale && dist!=0){
            distFinale=dist;
            (*cible)=(*liste)[i];
        }
    }
    //calcul de la nouvelle orientation
    //disjonction de cas
    double orientation;
    if (cible->getX()>=b.getX()){
        if (cible->getY()>=b.getY()){
            double orientation = std::acos((cible->getX()-b.getX())/distFinale);
        }
        else {
            double orientation = -std::acos((cible->getX()-b.getX())/distFinale);
        }
    }
    else {
        if (cible->getY()>=b.getY()){
            double orientation = M_PI-std::acos((b.getX()-cible->getX()/distFinale));
        }
        else {
            double orientation = -M_PI+std::acos((b.getX()-cible->getX()/distFinale));
        }
    }
    //On modifie l'orientation en conséquence
    b.setOrientation(orientation);
}
