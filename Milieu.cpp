#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{

   cout << "const Milieu" << endl;

   std::srand( time(NULL) );

}


Milieu::~Milieu( void )
{

   cout << "dest Milieu" << endl;

}


void Milieu::step( void )
{

   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {

      it->action( *this );
      it->draw( *this );
      for (std::vector<Bestiole>::iterator jt = listeBestioles.begin() ; jt != listeBestioles.end() ; ++jt){
         if (!(jt==it)){
            double dist = std::sqrt( (jt->getX()-it->getX())*(jt->getX()-it->getX()) + (jt->getY()-it->getY())*(jt->getY()-it->getY());
            if (dist<=8){
               int test = (rand() % 10 + 1);
               test = static_cast<double>(test)/10;
               if (test<=jt->getCollision()){
                  delete(jt);
               }
               else {
               jt->setOrientation();
               }
               if (test<=it->getCollision()){
                  delete(it);
               }
               else {
               it->setOrientation();
               }
            }
         }
      }
   } // for

}


int Milieu::nbVoisins( const Bestiole & b )
{

   int         nb = 0;


   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( !(b == *it) && b.jeTeVois(*it) )
         ++nb;

   return nb;

}
