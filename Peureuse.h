#ifndef _PEUREUSE_H_
#define _PEUREUSE_H_

#include <math.h>
#include "Comportement.h"
#include "Milieu.h"

using namespace std;

class Bestiole;
class Milieu;

class Peureuse : virtual public Comportement {

private:
    static const int tolerance;

private:
    double vitesse=0;
public:
    Peureuse(void);
    void comp(Bestiole& b, Milieu & monMilieu);
    T *getCouleur();

};

#endif