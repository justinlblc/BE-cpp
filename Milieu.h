#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Milieu : public UImg
{

private :
   static const T          white[];
   
   //Nageoire max
   static const double     v;

   //carapace
      //résistance max
   static const double     w;
      //réduction vitesse
   static const double     eta;

   //camouflage
      //minimum
   static const double     camoMin;
      //max
   static const double     camoMax;

   //Yeux
   static const double     alphaMin;
   static const double     alphaMax;

   static const double     distYeuxMin;
   static const double     distYeuxMax;

   static const double     detecYeuxMin;
   static const double     detecYeuxMax;

   //Oreille
   static const double     distOreiMin;
   static const double     distOreiMax;

   static const double     detecOreiMin;
   static const double     detecOreiMax;


private:
   int                     width, height;
   std::vector<std::shared_ptr<Bestiole>>   listeBestioles;

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( const Bestiole & b) {std::shared_ptr<Bestiole> best = make_shared<Bestiole>(b); listeBestioles.push_back(best); listeBestioles.back()->initCoords(width, height);}
   int nbVoisins( const Bestiole & b );

   //geter accesoires
   double getVmax();
   double getResmax();
   double getRedV();
   double getCamoMin();
   double getCamoMax();

   //geter capteurs
   double getAlphaMin();
   double getAlphaMax();
   double getDistYeuxMax();
   double getDistYeuxMin();
   double getDetecYeuxMin();
   double getDetecYeuxMax();
   double getDetecOreiMax();
   double getDetecOreiMin();
   double getDistOreiMin();
   double getDistOreiMax();
   
   std::vector<std::shared_ptr<Bestiole>> *getListeBestioles();

};


#endif
