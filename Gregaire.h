#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_

#include "Comportement.h"
#include <math.h>
#include "UImg.h"

using namespace std;

class Bestiole;
class Milieu;

class Gregaire : virtual public Comportement {
private:

    static int compteurGregaire;
public:
    Gregaire(void);
    void comp(Bestiole& b, Milieu & monMilieu);
    T * getCouleur();
};

#endif