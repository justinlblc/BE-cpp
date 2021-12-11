#include "Peureuse.h"
#include "Bestiole.h"
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

/*fonction du comportement de la bestiole peureuse
---
entrée: 
- bestiole qui possède le comportement
- son milieu

--- 
sortie : None
*/

void Peureuse::comp(Bestiole& b, Milieu & monMilieu){
    //nb voisin de la bestiole
    int nbVoisin = monMilieu.nbVoisins(b);

    //comparaison nbVoisin et tolérance
    if (nbVoisin>=tolerance ){
        //la bestiole n'était pas en fuite
        if (!(b.getFuis())){
            vitesse=b.getVitesse();
            b.setVitesse(b.getVMAX());
            b.setFuis(true); //La bestiole est en train de fuire    
        }
        b.setOrientation(-b.getOrientation()); //demi tour
    }
    //sortie de la fuite
    else if (nbVoisin<tolerance && b.getFuis()){
        b.setFuis(false); //La bestiole ne fuit pas
        b.setVitesse(this->vitesse);
    }
}

T *Peureuse::getCouleur(){
    return this->couleur;
}