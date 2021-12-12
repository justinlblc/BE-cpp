#ifndef _MULTIBESTIOLE_H_
#define _MULTIBESTIOLE_H_

#include <math.h>
#include "Comportement.h"
#include "Gregaire.h"
#include "Kamikaze.h"
#include "Peureuse.h"
#include "Prevoyante.h"

using namespace std;

class Bestiole;
class Milieu;
class MultiBestiole : public Bestiole
{
private:
    Gregaire *greg;
    Kamikaze *kami;
    Peureuse *peur;
    Prevoyante *prev;

    bool b1;
    bool b2;
    bool b3;
    bool b4;

public:
    // méthodes override
    MultiBestiole(Milieu &milieu, Gregaire *greg, Kamikaze *kami, Peureuse *peur, Prevoyante *prev);
    MultiBestiole(const MultiBestiole &b);
    void action(Milieu & monMilieu);
    bool isMulti() const;
    MultiBestiole &operator=(const MultiBestiole &b);
    // Nouvelles méthodes
    void setRandComp(Milieu & monMilieu);
    void setCouleur(T *couleur);
};

#endif