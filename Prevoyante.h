#ifndef _PREVOYANTE_H_
#define _PREVOYANTE_H_

#include <math.h>
#include "Comportement.h"
#include "Milieu.h"

using namespace std;

class Bestiole;
class Milieu;

class Prevoyante : virtual public Comportement {

public:
    Prevoyante(void);
    void comp(Bestiole& b, Milieu & monMilieu);
    T *getCouleur();

};

#endif