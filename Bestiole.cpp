#include "Bestiole.h"

#include "Milieu.h"

#include <cstdlib>
#include <cmath>


const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;

int               Bestiole::next = 0;


Bestiole::Bestiole( Milieu & milieu )
{
   //Accesories

   //Nageoires
   int ent = (int) floor(milieu.getVmax());
   double virg = milieu.getVmax() - (double) ent;
   int multient= (int) std::rand()%(ent-1)+1;
   double multivirg = (double) std::rand()/RAND_MAX;
   double multiV = (double) multient + multivirg;
   if (virg==0){
      multiV = (double) multient + multivirg;
   }
   else {
      while (multivirg>virg){
         multivirg = (double) std::rand()/RAND_MAX;
      }
      multiV = (double) multient + multivirg;
   }
   
   identite = ++next;
   collision = 0.2;
   clonage=0.003;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   AGE_LIM = (int) std::rand()%(1000-300)+300;
   age = 0;
   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = multiV*static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;
   cout<<vitesse<<endl;

   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

}


Bestiole::Bestiole( const Bestiole & b )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par copie" << endl;
   age=b.age;
   AGE_LIM=b.AGE_LIM;
   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = b.orientation;
   vitesse = b.vitesse;
   collision=b.collision;
   clonage=b.clonage;
   couleur = new T[ 3 ];
   memcpy( couleur, b.couleur, 3*sizeof(T) );

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

   bouge( monMilieu.getWidth(), monMilieu.getHeight());
   age++;
}


void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{

   return ( b1.identite == b2.identite );

}


bool Bestiole::jeTeVois( const Bestiole & b ) const
{

   double         dist;


   dist = std::sqrt( (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y) );
   return ( dist <= LIMITE_VUE );

}

int Bestiole::getX(){
   return this->x;
}
int Bestiole::getY(){
   return this->y;
}
void Bestiole::setOrientation(){
   this->orientation=M_PI - orientation;
}

double Bestiole::getCollision(){
   return this->collision;
}
Bestiole& Bestiole::operator=(const Bestiole& b){   
   if (this != &b){

      x=b.x;
      y=b.y;
      age=b.age;
      AGE_LIM=b.AGE_LIM;
      cumulX = cumulY = 0.;
      orientation=b.orientation;
      vitesse=b.vitesse;
      collision= b.collision;
      clonage=b.clonage;
      
      delete[] couleur;

      couleur = new T[ 3 ];
      couleur[0]=b.couleur[0];
      couleur[1]= b.couleur[1];
      couleur[2]= b.couleur[2];
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
   return clonage;
}

