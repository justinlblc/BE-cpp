#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>

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

private:
   int                     width, height;
   std::vector<Bestiole>   listeBestioles;

   

public :
   Milieu( int _width, int _height );
   ~Milieu( void );

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   void step( void );

   void addMember( const Bestiole & b ) { listeBestioles.push_back(b); listeBestioles.back().initCoords(width, height); }
   int nbVoisins( const Bestiole & b );

   //geter accesoires
   double getVmax();
   double getResmax();
   double getRedV();
   double getCamoMin();
   double getCamoMax();

};


#endif
