#include "Gregaire.h"
#include "Bestiole.h"
#include "Milieu.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

//Constructeur
Gregaire::Gregaire(void){
    couleur = new T[3];
    couleur[0]=248;
    couleur[1]=22;
    couleur[2]=15;
    return;
};

/*
"b" est la bestiole grégaire dans le milieu "monMilieu"
Si "b" a des voisins, "b" aura pour orientation la moyenne de celle de ces voisins

Input: 
  -  Bestiole grégaire "b" 
  -  Son milieu "monMilieu"

Output: none
*/
void Gregaire::comp(Bestiole& b, Milieu & monMilieu){
    //future orientation
    double orientation;
    
    int nbVoisin = monMilieu.nbVoisins(b);
    if (nbVoisin>=1){
        int k = monMilieu.getListeBestioles()->size();
        std::vector<std::shared_ptr<Bestiole>> *liste = monMilieu.getListeBestioles();
        //boucle incrémentant l'orientation des voisins de "b"
        for (int i =0;i<k;i++ ){
            if ( !(b == *(*liste)[i]) && b.jeTeVois(*(*liste)[i])){
                orientation+=(*liste)[i]->getOrientation();
            }
        }
        if (b.getOrientation()!=orientation){
            b.setOrientation(orientation/nbVoisin);
        }
    }
}

T *Gregaire::getCouleur(){
    return this->couleur;
}
