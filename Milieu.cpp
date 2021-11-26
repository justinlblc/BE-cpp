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

std::vector<int> Milieu::collision(){
   std::vector<int> collisions;
   int k = static_cast<int>(listeBestioles.size());
   for (int i =0; i<k; i++){
      for (int j = 0; j<k;i++){
         if(!(listeBestioles[i]==listeBestioles[j])){
            double dist = std::sqrt((listeBestioles[j].getX()-listeBestioles[i].getX())*(listeBestioles[j].getX()-listeBestioles[i].getX()) + (listeBestioles[j].getY()-listeBestioles[i].getY())*(listeBestioles[j].getY()-listeBestioles[i].getY()));
            if (dist<=8){
               collisions.push_back(i);
               collisions.push_back(j);
            }
         }
      }
   }
   std::sort(collisions.begin(), collisions.end());
   auto last = std::unique(collisions.begin(), collisions.end());
   collisions.erase(last, collisions.end());
}

void Milieu::step( void ){
   std::vector<int> collisions = this->collision();
   int k = static_cast<int>(colissions.size());
   for (int i =0; i<collisions.size();i++){
      double v = std::rand();
      if (v<listeBestioles[i].getCollision()){
         listeBestioles.erase(listeBestioles.begin() + i);
         for (int j = i+1; j<collisions.size();j++){
            collisions[j]-=1;
         }
      }
      else {
         listeBestioles[i].setOrientation();
      }
   }
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   int i = 0;
   
   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {
      it->action( *this );
      it->draw( *this );  
}


int Milieu::nbVoisins( const Bestiole & b ){

   int         nb = 0;


   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( !(b == *it) && b.jeTeVois(*it) )
         ++nb;

   return nb;

}
