#include "Milieu.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <memory>

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };

//Nageoire: 
   //vitesse max
const double    Milieu::v=3.;

//Carapace:
   //Résistance max
const double    Milieu::w=2.;
   //Réduction vitesse max
const double    Milieu::eta=3;

//Camouflage
   //Minimum
const double    Milieu::camoMin=0;
   //Maximum (plus petit que 1)
const double    Milieu::camoMax=1;

//yeux
const double    Milieu::alphaMin = 0;
const double    Milieu::alphaMax = M_PI;

//Distance min doit être cohérente avec la limite de distance pour la collision
const double    Milieu::distYeuxMin = 30;
const double    Milieu::distYeuxMax = 40;

const double    Milieu::detecYeuxMin = 0;
const double    Milieu::detecYeuxMax = 1;

//oreilles

const double     Milieu::distOreiMin = 4;
const double     Milieu::distOreiMax = 30;

const double     Milieu::detecOreiMin = 0;
const double     Milieu::detecOreiMax = 1;



Milieu::Milieu( int _width, int _height) : UImg( _width, _height, 1, 3 ),
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
   int t = listeBestioles.size();
   for ( int i = 0; i<t;i++)
   {
      listeBestioles[i]->action( *this );
      listeBestioles[i]->draw( *this );
   }
   std::vector<int> collisions;
   int k = listeBestioles.size();
   for (int i = 0; i<k; i++){
      if (listeBestioles[i]->getAge()==listeBestioles[i]->getAgeLim()){
         listeBestioles.erase(listeBestioles.begin() +i);
         cout<<"mort spontanée"<<endl;
         break;
      }
   }
   for (int i = 0; i<k; i++){
      for (int j = i; j<k; j++){
         double dist = std::sqrt((listeBestioles[i]->getX()-listeBestioles[j]->getX())*(listeBestioles[i]->getX()-listeBestioles[j]->getX())+(listeBestioles[i]->getY()-listeBestioles[j]->getY())*(listeBestioles[i]->getY()-listeBestioles[j]->getY()));
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
      if (test<=listeBestioles[collisions[i]]->getCollision()){
         listeBestioles.erase(listeBestioles.begin() + collisions[i]);
         if (i!=m-1){
            for (int j=i+1;j<m;j++){
               collisions[j]=collisions[j]-1;
            }
         }
      }
      else{
         listeBestioles[collisions[i]]->setOrientation(M_PI - listeBestioles[collisions[i]]->getOrientation());
      }
   }
   for (int i = 0; i<k; i++){
      double test = (double) std::rand()/RAND_MAX;
      if (test<=listeBestioles[i]->getClonage()){
         this->addMember(*listeBestioles[i]);
         cout<<"Clonage"<<endl;
         break;
      }
   }
}

int Milieu::nbVoisins( const Bestiole & b ){

   int         nb = 0;

   int k = listeBestioles.size();
   for ( int i = 0; i<k; i++){
      if ( !(b == (*listeBestioles[i])) && b.jeTeVois(*listeBestioles[i]) ){
         ++nb;
      }
   }
   return nb;

}

double Milieu::getVmax(){
   return this->v;
}

double Milieu::getResmax(){
   return this->w;
}

double Milieu::getRedV(){
   return this->eta;
}

double Milieu::getCamoMin(){
   return this->camoMin;
}

double Milieu::getCamoMax(){
   return this->camoMax;
}

double Milieu::getAlphaMin(){
   return this->alphaMin;
}
double  Milieu::getAlphaMax(){
   return this->alphaMax;
}
double  Milieu::getDistYeuxMax(){
   return this->distYeuxMax;
}
double  Milieu::getDistYeuxMin(){
   return this->distYeuxMin;
}
double  Milieu::getDetecYeuxMin(){
   return this->detecYeuxMin;
}
double  Milieu::getDetecYeuxMax(){
   return this->detecYeuxMax;
}

double Milieu::getDetecOreiMax(){
   return this->detecOreiMin;
}

double Milieu::getDetecOreiMin(){
   return this->detecOreiMax;
}

double Milieu::getDistOreiMin(){
   return this->distOreiMin;
}

double Milieu::getDistOreiMax(){
   return this->distOreiMax;
}
   

std::vector<std::shared_ptr<Bestiole>> *Milieu::getListeBestioles(){
   std::vector<std::shared_ptr<Bestiole>> * ptr_listeBestioles= &listeBestioles; 
   return ptr_listeBestioles;
}