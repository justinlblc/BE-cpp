#include "Milieu.h"
#include "Bestiole.h"
#include "MultiBestiole.h"
#include "Gregaire.h"
#include "Kamikaze.h"
#include "Peureuse.h"
#include "Prevoyante.h"

#include <algorithm>
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

//naissance

const double Milieu::naissance=0.1;
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

bool predicatMortSpontanee(std::shared_ptr<Bestiole> b){
   //cout<<"Age de la bestiole: "<<b->getAge()<<endl;
   //cout <<"Son âge limite: "<<b->getAgeLim()<<endl;
   //cout << (b->getAge()>=b->getAgeLim())<<endl;
   if (b->getAge()>=b->getAgeLim()){
      //cout<<"Mort spontanée"<<endl;
   }
   return (b->getAge()>=b->getAgeLim());
}

Milieu::Milieu( int _width, int _height,  bool b1, bool b2, bool b3, bool b4, Gregaire * greg, Kamikaze * kami, Peureuse * peur, Prevoyante * prev) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{
   this->b1=b1;
   this->b2=b2;
   this->b3=b3;
   this->b4=b4;

   this->greg=greg;
   this->kami=kami;
   this->peur=peur;
   this->prev=prev;
   
   cout << "const Milieu" << endl;
   std::srand( time(NULL) );

}


Milieu::~Milieu( void )
{
   
   cout << "dest Milieu" << endl;
}


/*
Fonction de naissance spontanée. Tire un nombre aléatoire pour savoir quel type de bestoile va nâitre.

Input: None

Output: None
*/
void Milieu::naissanceSpont(){
   double nait = static_cast<double>( std::rand() )/RAND_MAX;
   if (nait<this->naissance){
      cout<<nait<<endl;
      int i = std::rand()% 5 +1;
      //cout<<"Nombre aléatoire: "<<i<<endl;
      if (i==1 && b1==true){
         Bestiole * b = new Bestiole(*this, this->greg);
         //this->addMember(*(new Bestiole(*this, this->greg)));
         addMember(*b);
         cout<<"Naissance spontanée Grégaire."<<endl;
      }
      else if (i==2 && b2==true){
         Bestiole * b = new Bestiole(*this, this->kami);
         //this->addMember(*(new Bestiole(*this, this->kami)));
         addMember(*b);
         cout<<"Naissance spontanée Kamikaze."<<endl;
      }
      else if (i==3 && b3==true){
         Bestiole * b = new Bestiole(*this, this->peur);
         //this->addMember(*(new Bestiole(*this, this->peur)));
         addMember(*b);
         cout<<"Naissance spontanée Peureuse."<<endl;
      }
      else if (i==4 && b4==true){
         Bestiole * b = new Bestiole(*this, this->prev);
         //this->addMember(*(new Bestiole(*this, this->prev)));
         addMember(*b);
         cout<<"Naissance spontanée Prévoyante."<<endl;
      }
      else if (i==5){
         Bestiole * b = new MultiBestiole(*this, b1, b2, b3, b4, greg, kami, peur, prev);
         //this->addMember(*(new MultiBestiole(*this, b1, b2, b3, b4, this->greg, this->kami, this->peur, this->prev)));
         addMember(*b);
         cout<<"Naissance spontanée Multibestiole"<<endl;        
      }
      else {
         naissanceSpont();
      }
   }
}

void Milieu::step( void ){
   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   //Naissance spontanée
   //naissanceSpont();

   //Mouvement des bestioles à chaque pas de la simulation
   int t = listeBestioles.size();
   for ( int i = 0; i<t;i++)
   {
      listeBestioles[i]->action( *this );
      listeBestioles[i]->draw( *this );
   }

   //mort spontanée
   //for (int i = 0; i<t; i++){
      //if (listeBestioles[i]->getAge()==listeBestioles[i]->getAgeLim()){
         //listeBestioles.erase(listeBestioles.begin() +i);
         //cout<<"Mort spontanée"<<endl;
         //break;
      //}
   //}
   listeBestioles.erase(std::remove_if(listeBestioles.begin(), listeBestioles.end(),predicatMortSpontanee), listeBestioles.end());
   int k = listeBestioles.size();

   //Clonage des bestioles
   for (int i = 0; i<k; i++){
      double test = (double) std::rand()/RAND_MAX;
      if (test<=listeBestioles[i]->getClonage()){
         //cout<<"On va cloner une bestiole..."<<endl;
         this->addMember(*listeBestioles[i]);
         //cout<<"Clonage"<<endl;
      }
   }
 
   k = listeBestioles.size();
   //Vecteur contenant les indices des bestioles qui rentrent en collisions à linstant t.
   //L'indice est celui des bestioles dans listeBestioles
   std::vector<int> collisions;
   for (int i = 0; i<k; i++){
      for (int j = i; j<k; j++){
         double dist = std::sqrt((listeBestioles[i]->getX()-listeBestioles[j]->getX())*(listeBestioles[i]->getX()-listeBestioles[j]->getX())+(listeBestioles[i]->getY()-listeBestioles[j]->getY())*(listeBestioles[i]->getY()-listeBestioles[j]->getY()));
         //Si les deux bestioles se touchent, on rajoute leurs indices à la liste
         if (dist<8 && j!=i){
            collisions.push_back(j);
            collisions.push_back(i);
         }
      } 
   }

   //On trie par ordre croissant et on supprime les doublons de la liste d'indices
   std::sort(collisions.begin(), collisions.end());
   auto last = std::unique(collisions.begin(),collisions.end());
   collisions.erase(last, collisions.end());
   
   //Pour chaque bestiole en collision, si le nombre aléatoire est plus petit que sa probabilité de mourir à chaque collision, elle meurt, sinon elle fait demi-tour
   int m = collisions.size();
   for(int i = 0; i<m;i++){
      double test = (double) std::rand() / (RAND_MAX);
      if (test<=listeBestioles[collisions[i]]->getCollision()){
         //cout<<"Attention mort par collision"<<endl;
         listeBestioles.erase(listeBestioles.begin() + collisions[i]);
         //cout<<"Mort par collision"<<endl;
         //On décale les indices suivant de -1
         if (i!=m-1){
            //cout<<"Pb de segmentation?"<<endl;
            for (int j=i+1;j<m;j++){
               collisions[j]=collisions[j]-1;
            }
            //cout<<"Non"<<endl;
         }
      }
      else{
         listeBestioles[collisions[i]]->setOrientation(M_PI - listeBestioles[collisions[i]]->getOrientation());
      }
   }
}


//Donne le nombre de bestiole que voit une bestiole donnée
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

//Ajoute une bestiole b à listeBestioles
void Milieu::addMember(const Bestiole & b){
   //Cas d'une multibestiole
   if (b.isMulti()){
      //Nécessité de caster pour éviter le phénomène de slicing dû au polymorhpisme
      std::shared_ptr<MultiBestiole> best = make_shared<MultiBestiole>(dynamic_cast<MultiBestiole&>(const_cast<Bestiole&>(b))); 
      listeBestioles.push_back(best); 
      listeBestioles.back()->initCoords(width, height);
   }
   //cas d'une bestiole normale
   else {
      std::shared_ptr<Bestiole> best = make_shared<Bestiole>(b); 
      listeBestioles.push_back(best); 
      listeBestioles.back()->initCoords(width, height);
   }
}

//Liste des geter
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