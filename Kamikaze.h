#ifndef _KAMIKAZE_H_
#define _KAMIKAZE_H_

#include <math.h>
#include "Comportement.h"

using namespace std;

class Bestiole;
class Milieu;

class Kamikaze : virtual public Comportement {

private:
    Bestiole    * b;

public:
    Kamikaze(void);
    void comp(Bestiole& b, Milieu & monMilieu);
    T * getCouleur();

};

#endif