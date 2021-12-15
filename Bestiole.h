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
   static T              * couleurCarap;

   static const double      CARAPACE;
   static const double      CAMOUFLAGE;
   static const double      NAGEOIRES;

   static const double      OREILLES;
   static const double      YEUX;

protected :
   int               AGE_LIM;

   Comportement    * comp;
   int               identite;
   int               x, y;
   int               age;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   //Probabilité de mourir lors d'une collision
   double            collision;
   //Probabilité de se cloner à chaque pas de la simulation
   double            clonage;
   T               * couleur;

   bool              fuis=false;
   //Accessoires
   double            camo;
   double            multiRedV;
   double            multiV;
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
   virtual ~Bestiole( void );                                    // Destructeur
                                                         // Operateur d'affectation binaire par defaut
   virtual void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );
   virtual Bestiole& operator=(const Bestiole& bestiole);
   
   void setOrientation(double orientation);
   void setVitesse(double vitesse);
   void setFuis(bool fuis){this->fuis=fuis;};

   int getX();
   int getY();
   double getCollision();
   int getAge();
   int getAgeLim();
   double getClonage();
   double getOrientation();
   double getVitesse();
   double getVMAX(){return MAX_VITESSE;};
   Comportement *getComp();
   bool getFuis(){return fuis;};
   double getDist();

   virtual bool isMulti() const;
};


#endif
