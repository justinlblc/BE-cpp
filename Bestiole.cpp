#include "Bestiole.h"
#include "Comportement.h"
#include "Gregaire.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>

//Constantes propres à toutes les bestioles
const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
//const double      Bestiole::LIMITE_VUE = 30.;

int               Bestiole::next = 0;

T                *Bestiole::couleurCarap = new T[3];

//prend en entrée 2 flottant et renvoie un flottant aléatoire entre les deux
double Rand(double min, double max){
   int m = ceil(min*100);
   int M = floor (max * 100);
   double rand = (double) (std::rand()%(M-m)+m);
   return rand/100;
}

//constructeur
Bestiole::Bestiole( Milieu & milieu, Comportement * comp){
   this->comp=comp;

   //Accesoires
      //Nageoires
   double multiV=Rand(1, milieu.getVmax());

      //Carapace
         //resistance
   double multiW=Rand(1, milieu.getResmax());
         //reduction de la vitesse
   double multiRedV=Rand(1, milieu.getRedV());

      //Camouflage
   camo = Rand(milieu.getCamoMin(), milieu.getCamoMax());
   
   //Capteur
      //Yeux
         //angle
   angle = Rand(milieu.getAlphaMin(), milieu.getAlphaMax());
         //distance
   yeuxDist = Rand(milieu.getDistYeuxMin(), milieu.getDistYeuxMax());
         //Capacité de detection
   yeuxDetec = Rand(milieu.getDetecYeuxMin(), milieu.getDetecYeuxMax());

      //Oreilles
   oreiDetec = Rand(milieu.getDetecOreiMin(), milieu.getDetecOreiMax());
   oreiDist = Rand(milieu.getDistOreiMin(), milieu.getDistOreiMax());

   collision = 0.2/multiW;
   clonage=0.003;

   identite = ++next;

   //Âge
   AGE_LIM = (int) std::rand()%(1000-300)+300;
   age = 0;

   //coordonnées, vitesse et orientation initiale
   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = (multiV*static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE)/multiRedV;

   if (vitesse>MAX_VITESSE){
      vitesse = MAX_VITESSE;
   }

   //On initialise la couleur à la couleur du comportement correspondant
   couleur = new T[ 3 ];
   T *couleurComp= comp->getCouleur();
   couleur[ 0 ] = couleurComp[0];
   couleur[ 1 ] = couleurComp[1];
   couleur[ 2 ] = couleurComp[2];

   couleurCarap[0] = 0;
   couleurCarap[1] = 0;
   couleurCarap[2] = 0;
}


Bestiole::Bestiole( const Bestiole & b){  

   fuis=b.fuis;
   collision=b.collision;
   clonage=b.clonage;
   camo=b.camo;
   //capteurs
   //yeux
   angle=b.angle;
   yeuxDist = b.yeuxDist;
   yeuxDetec = b.yeuxDetec;

   //Oreilles
   oreiDetec = b.oreiDetec;
   oreiDist = b.oreiDist;



   identite = ++next;


   age=b.age;
   AGE_LIM=b.AGE_LIM;

   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   couleur = new T[ 3 ];
   memcpy( couleur, b.couleur, 3*sizeof(T) );

   this->comp=b.comp;
}


Bestiole::~Bestiole( void )
{

   delete[] couleur;

   //cout << "dest Bestiole" << endl;

}
Bestiole& Bestiole::operator=(const Bestiole& b){   
   if (this != &b){

      collision= b.collision;
      clonage=b.clonage;

      x=b.x;
      y=b.y;

      camo=b.camo;
      //capteurs
      //yeux
      angle=b.angle;
      yeuxDist = b.yeuxDist;
      yeuxDetec = b.yeuxDetec;

      //Oreilles
      oreiDetec = b.oreiDetec;
      oreiDist = b.oreiDist;

      age=b.age;
      AGE_LIM=b.AGE_LIM;

      cumulX = cumulY = 0.;
      orientation=b.orientation;
      vitesse=b.vitesse;
      clonage=b.clonage;
      
      delete[] couleur;

      couleur = new T[ 3 ];
      couleur[0]=b.couleur[0];
      couleur[1]= b.couleur[1];
      couleur[2]= b.couleur[2];
      comp=b.comp;
      fuis=b.fuis;
   }
   return *this;
}
//Initialise les coordonnées initiales aléatoirement
void Bestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

}


/*
change la direction si la bestiole s'apprête à les dépasser
input :  taille du milieu

output: none

*/
void Bestiole::bouge( int xLim, int yLim )
{

   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;


   cx = static_cast<int>( cumulX ); cumulX -= cx;
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;
   ny = y + dy + cy;

   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }
}

/*
Input: Prend en paramètre le milieu
   Execute la fonction "comp" propre au comportement de la bestiole
Output: none
*/
void Bestiole::action( Milieu & monMilieu )
{  
   //appel du comportement
   comp->comp(*this, monMilieu);
   bouge( monMilieu.getWidth(), monMilieu.getHeight());
   age++;
}

/*
Dessine la bestiole
Input : support
Output: none
*/
void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

   //Dessin de la carapace
   support.draw_circle(x,y,AFF_SIZE/4., couleurCarap, 10000000);

}

/*
ré-ecriture de l'opérateur ==
*/
bool operator==( const Bestiole & b1, const Bestiole & b2 )
{

   return ( b1.identite == b2.identite );

}

/*
Fonction de detection. 

Input : bestiole "b". 
Output: Booléen - true si la bestiole "this" detecte (Voit ou Entend) la bestiole "b" 
                - false sinon
*/
bool Bestiole::jeTeVois( const Bestiole & b ) const
{
   //capacité de detection
   if (oreiDetec<b.oreiDetec || yeuxDetec<b.camo){
      return false;
   }

   //Distance entre la bestiole "this" et la bestiole "b"
   double dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );

   //Oreilles
   if (dist<oreiDist){
      return true;
   }
   
   //Yeux --Pour être vu, la bestiole "b" doit être assez proche et dans le bon angle de vu: le champ de vision
      //Test de la distance
   if (dist>yeuxDist){
      return false;
   }
      //Test de l'angle
   //Angle formé entre l'horizontale et l'axe reliant les deux bestioles
   double ori = std::acos((b.x-x)/dist);
   if (b.y<y){
      ori = -ori;
   }
   //Valeurs extrêmes des champs de vision
   double orientationMax = orientation + angle/2;
   double orientationMin = orientation - angle/2;


   //RAPPEL: orientation € ]-M_PI, M_PI[
   //Si la borne inférieur du champ de vision est inférieur à -M_PI:
   if (orientationMin<-M_PI){
      orientationMin += 2*M_PI;
      if (ori>orientationMin || ori<orientationMax){
         return true;
      }
   }
   //Si la borne supérieur du champ de vision est supérieure à M_PI
   else if (orientationMax>M_PI){
      orientationMax -=2*M_PI;
      if (ori>orientationMin || ori<orientationMax){
         return true;
      }
   }

   //Test champs de vision
   if (ori>orientationMin && ori<orientationMax){
      return true;
   }

   //On renvoie false dans tout autre cas
   return false;
}

//setter
void Bestiole::setOrientation(double orientation){
   this->orientation=orientation;
}

void Bestiole::setVitesse(double vitesse){
   this->vitesse=vitesse;
}

//getter   
int Bestiole::getX(){
   return this->x;
}
int Bestiole::getY(){
   return this->y;
}

double Bestiole::getCollision(){
   return this->collision;
}


int Bestiole::getAge(){
   return age;
}

int Bestiole::getAgeLim(){
   return AGE_LIM;
}

double Bestiole::getClonage(){
   return this->clonage;
}

double Bestiole::getOrientation(){
   return this->orientation;
}

double Bestiole::getVitesse(){
   return this->vitesse;
}


Comportement *Bestiole::getComp(){
   return this->comp;
}


//La bestiole n'est pas une MultiBestiole
bool Bestiole::isMulti() const{
   return false;
}