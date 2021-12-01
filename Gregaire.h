#ifndef _GREGAIRE_H_
#define _GREGAIRE_H_

#include <math.h>
#include "Comportement.h"
#include "Milieu.h"

using namespace std;

class Bestiole;
class Milieu;

class Gregaire : virtual public Comportement {

public:
    Gregaire(void);
    void comp(Bestiole& b, Milieu & monMilieu);

};

#endif