#include "Kamikaze.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

using namespace std;

Kamikaze::Kamikaze(void){
    couleur = new T[3];
    couleur[0]=39;
    couleur[1]=118;
    couleur[2]=32;
    return;
};

//La bestiole kamikaze se dirige vers la bestiole la plus proche qu'elle détecte pour rentrer en collision avec elle
void Kamikaze::comp(Bestiole& b, Milieu & monMilieu){
    std::vector<std::shared_ptr<Bestiole>> *liste = monMilieu.getListeBestioles();
    int k = liste->size();
    //distance initialisée comme la plus grande possible
    double distCourte = monMilieu.getWidth();
    //int stocke la valeur de l'index du voisin le plus proche dans listeBestioles
    int index;
    //Boucle: si "b" détecte une bestiole plus proche que la précédente, on stocke cette distance dans distCourte.
    for (int i=0; i<k;i++){
        if (b.jeTeVois(*(*liste)[i]) && !(*(*liste)[i]==b)){
            double dist = std::sqrt((b.getX()-(*liste)[i]->getX())*(b.getX()-(*liste)[i]->getX())+((b.getY()-(*liste)[i]->getY()))*((b.getY()-(*liste)[i]->getY())));
            if (dist < distCourte){
                distCourte = dist;
                index=i;
            }
        }
    }
    //Si "b" a au moins un voisin
    if (distCourte!=monMilieu.getWidth()){
        //Angle entre l'horizontale et l'axe reliant les deux bestioles
        double orientation = std::acos(((*liste)[index]->getX()-b.getX())/distCourte);
        if ((*liste)[index]->getY()>b.getY()){
            orientation = -orientation;
        }
        if (b.getOrientation()!=orientation){
            b.setOrientation(orientation);
        }
    }
}

T *Kamikaze::getCouleur(){
    return this->couleur;
}


