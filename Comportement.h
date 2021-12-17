#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_

#include <vector>
#include "UImg.h"

using namespace std;

class Bestiole;
class Milieu;

class Comportement {
    protected:
        T * couleur;
    public:
        virtual void comp(Bestiole& b, Milieu & monMilieu)=0;       //Fonction définissant les mouvements propres au comportement
        virtual T * getCouleur()=0;                             //récupère la couleur propre au comportement                                
};


#endif