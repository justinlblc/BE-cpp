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

void Milieu::step( void ){
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   
   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {
      it->action( *this );
      it->draw( *this );
   }
   std::vector<int> collisions;
   int k = listeBestioles.size();
   for (int i = 0; i<k; i++){
      if (listeBestioles[i].getAge()==listeBestioles[i].getAgeLim()){
         listeBestioles.erase(listeBestioles.begin() +i);
         cout<<"mort spontanée"<<endl;
         break;
      }
   }
   for (int i = 0; i<k; i++){
      for (int j = i; j<k; j++){
         double dist = std::sqrt((listeBestioles[i].getX()-listeBestioles[j].getX())*(listeBestioles[i].getX()-listeBestioles[j].getX())+(listeBestioles[i].getY()-listeBestioles[j].getY())*(listeBestioles[i].getY()-listeBestioles[j].getY()));
         if (dist<8 && j!=i){
            collisions.push_back(j);
            collisions.push_back(i);
         }
      } 
   }
   std::sort(collisions.begin(), collisions.end());
   auto last = std::unique(collisions.begin(),collisions.end());
   collisions.erase(last, collisions.end());
   
   int m = collisions.size();
   for(int i = 0; i<m;i++){
      double test = (double) std::rand() / (RAND_MAX);
      if (test<=listeBestioles[collisions[i]].getCollision()){
         listeBestioles.erase(listeBestioles.begin() + collisions[i]);
         if (i!=m-1){
            for (int j=i+1;j<m;j++){
               collisions[j]=collisions[j]-1;
            }
         }
      }
      else{
         listeBestioles[collisions[i]].setOrientation();
      }
   }
   for (int i = 0; i<k; i++){
      double test = (double) std::rand()/RAND_MAX;
      if (test<=listeBestioles[i].getClonage()){
         cout<<"test: "<< test<<"clonage: "<<listeBestioles[i].getClonage();
         this->addMember(listeBestioles[i]);
         cout<<"Clonage"<<endl;
         break;
      }
   }
}

int Milieu::nbVoisins( const Bestiole & b ){

   int         nb = 0;


   for ( std::vector<Bestiole>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( !(b == *it) && b.jeTeVois(*it) )
         ++nb;
   return nb;

}