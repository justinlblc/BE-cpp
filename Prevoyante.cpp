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
    
}

T *Prevoyante::getCouleur(){
    return this->couleur;
}

