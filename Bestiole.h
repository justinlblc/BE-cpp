#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include <iostream>

using namespace std;


class Milieu;
class Comportement;

class Bestiole
{

protected :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static int              next;

protected :
   int               AGE_LIM;

   Comportement    * comp;
   int               identite;
   int               x, y;
   int               age;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   double            collision;
   double            clonage;
   T               * couleur;

   bool              fuis=false;
   
   double            camo;

   //capteur
      //yeux
   double            angle;
   double            yeuxDist;
   double            yeuxDetec;
      //oreilles
   double            oreiDetec;
   double            oreiDist;

protected :
   void bouge( int xLim, int yLim );

public :                                                 // Forme canonique :
   Bestiole(Milieu & milieu, Comportement * comp);  // Constructeur par defaut
   Bestiole( const Bestiole & b );                       // Constructeur de copies
   ~Bestiole( void );                                    // Destructeur
                                                         // Operateur d'affectation binaire par defaut
   virtual void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );
   int getX();
   int getY();
   void setOrientation(double orientation);
   void setVitesse(double vitesse);
   double getCollision();
   int getAge();
   int getAgeLim();
   double getClonage();
   double getOrientation();
   double getVitesse();
   double getVMAX(){return MAX_VITESSE;};
   Comportement *getComp();
   bool getFuis(){return fuis;};
   void setFuis(bool fuis){this->fuis=fuis;};

   Bestiole& operator=(const Bestiole& bestiole);

   double getDist();
};


#endif
