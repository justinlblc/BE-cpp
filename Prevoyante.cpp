#include "Prevoyante.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Prevoyante::Prevoyante(void){
    couleur = new T[3];
    couleur[0]=238;
    couleur[1]=49;
    couleur[2]=226;
    return;
};

void Prevoyante::comp(Bestiole& b, Milieu & monMilieu){
    std::vector<Bestiole> *liste = monMilieu.getListeBestioles();
    int k = liste->size();
    double distCourte = monMilieu.getWidth();
    int index;
    for (int i=0; i<k;i++){
        if (b.jeTeVois((*liste)[i]) && !((*liste)[i]==b)){
            double dist = std::sqrt((b.getX()-(*liste)[i].getX())*(b.getX()-(*liste)[i].getX())+((b.getY()-(*liste)[i].getY()))*((b.getY()-(*liste)[i].getY())));
            if (dist < distCourte){
                distCourte = dist;
                index=i;
            }
        }
    }
    if (distCourte!=monMilieu.getWidth()){
        double orientation = std::acos(((*liste)[index].getX()-b.getX())/distCourte);
        if ((*liste)[index].getY()<b.getY()){
            orientation = -orientation;
        }
        b.setOrientation(orientation);
    }
    
    }

T *Prevoyante::getCouleur(){
    return this->couleur;
}

