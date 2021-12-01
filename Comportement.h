#ifndef _COMPORTEMENT_H_
#define _COMPORTEMENT_H_

#include "Comportement.h"
#include "Milieu.h"
#include <vector>

using namespace std;

class Bestiole;
class Milieu;

class Comportement {

    public:
        virtual void comp(Bestiole& b, Milieu & monMilieu)=0;
};


#endif