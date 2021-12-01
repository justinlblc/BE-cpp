#include "Gregaire.h"
#include "Bestiole.h"
#include "Comportement.h"
#include "Milieu.h"
#include <iostream>
#include <vector>

using namespace std;


Gregaire::Gregaire(void){
    return;
};

void Gregaire::comp(Bestiole& b, Milieu & monMilieu){
    double orientation;
    int nbVoisin = monMilieu.nbVoisins(b);
    cout<<"Nb voisins: " << monMilieu.nbVoisins(b)<<endl;
    if (nbVoisin>=1){
        int k = monMilieu.getListeBestioles()->size();
        std::vector<Bestiole> *liste = monMilieu.getListeBestioles();
        for (int i =0;i<k;i++ ){
            if ( !(b == (*liste)[i]) && b.jeTeVois((*liste)[i])){
                orientation+=(*liste)[i].getOrientation();
                cout<<"Comportement Grégaire"<<endl;
            }
        }
    }
    //b.setOrientation(orientation/nbVoisin);

}
