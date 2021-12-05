#include "Bestiole.h"
#include "Comportement.h"
#include "Gregaire.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>


const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;

int               Bestiole::next = 0;

double Rand(double min, double max){
   int m = ceil(min*100);
   int M = floor (max * 100);
   double rand = (double) (std::rand()%(M-m)+m);
   return rand/100;
}


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
   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   AGE_LIM = (int) std::rand()%(1000-300)+300;
   age = 0;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = (multiV*static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE)/multiRedV;

   if (vitesse>MAX_VITESSE){
      vitesse = MAX_VITESSE;
   }

   couleur = new T[ 3 ];
   T *coul= comp->getCouleur();
   couleur[ 0 ] = coul[0];
   couleur[ 1 ] = coul[1];
   couleur[ 2 ] = coul[2];
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

   cout << "const Bestiole (" << identite << ") par copie" << endl;

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

   cout << "dest Bestiole" << endl;

}


void Bestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

}


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


void Bestiole::action( Milieu & monMilieu )
{  
   comp->comp(*this, monMilieu);
   bouge( monMilieu.getWidth(), monMilieu.getHeight());
   age++;
}

void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );
   T *coul = new T[3];
   coul[0]=coul[1]=coul[2]=0;
   support.draw_circle(x,y,AFF_SIZE/4., coul, 10000000);

}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{

   return ( b1.identite == b2.identite );

}


bool Bestiole::jeTeVois( const Bestiole & b ) const
{
   double dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   //Oreilles
   if (dist<oreiDist){
      return true;
   }
   
   //Yeux
   if (dist>yeuxDist){
      return false;
   }

   //Angle formé entre l'horizontale et l'axe reliant les deux bestioles
   double ori = std::acos((b.x-x)/dist);
   if (b.y<y){
      ori = -ori;
   }
   //Oreille
   double orientationMax = orientation + angle/2;
   double orientationMin = orientation - angle/2;

   //Si le min est inférieur à M_PI:
   if (orientationMin<-M_PI){
      orientationMin += 2*M_PI;
      if (ori>orientationMin || ori<orientationMax){
         return true;
      }
   }
   //Si le max est supérieur à M_PI:
   else if (orientationMax>M_PI){
      orientationMax -=2*M_PI;
      if (ori>orientationMin || ori<orientationMax){
         return true;
      }
   }
   if (ori>orientationMin && ori<orientationMax){
      return true;
   }
   return false;
}
   
   
int Bestiole::getX(){
   return this->x;
}
int Bestiole::getY(){
   return this->y;
}
void Bestiole::setOrientation(double orientation){
   this->orientation=orientation;
}

double Bestiole::getCollision(){
   return this->collision;
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

void Bestiole::setVitesse(double vitesse){
   this->vitesse=vitesse;
}

Comportement *Bestiole::getComp(){
   return this->comp;
}