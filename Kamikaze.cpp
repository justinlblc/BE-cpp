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
    if (k>1){
        int l = 0
        double distFinale = monMilieu.getWidth();
        for (int i =0; i<k;i++){
            double dist = std::sqrt(b.getX()-(*liste)[i].getX())*(b.getX()-(*liste)[i].getX())+(b.getY()-(*liste)[i].getY())*(b.getY()-(*liste)[i].getY()));
            if (dist<distFinale && dist!=0){
                distFinale=dist;
                l =i;
            }
        }
        //calcul de la nouvelle orientation
        //disjonction de cas
        Bestiole *cible = &(*liste[l]);
        double orientation;
        if (cible->getX()>=b.getX()){
            if (cible->getY()>=b.getY()){
                orientation = std::acos((cible->getX()-b.getX())/distFinale);
            }
            else {
                orientation = -std::acos((cible->getX()-b.getX())/distFinale);
            }
        }
        else {
            if (cible->getY()>=b.getY()){
                orientation = M_PI-std::acos((b.getX()-cible->getX()/distFinale));
            }
            else {
                orientation = -M_PI+std::acos((b.getX()-cible->getX()/distFinale));
            }
        }
        //On modifie l'orientation en conséquence
        b.setOrientation(orientation);
    }
}

