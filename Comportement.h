#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_

#include "Comportement.h"
#include "Milieu.h"
#include <vector>

using namespace std;

class Bestiole;
class Milieu;

class Comportement {
    protected:
        T * couleur;
    public:
        virtual void comp(Bestiole& b, Milieu & monMilieu)=0;
        virtual T * getCouleur()=0;
};


#endif