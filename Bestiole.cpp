#include "Bestiole.h"
#include "Comportement.h"
#include "Gregaire.h"
#include "Milieu.h"

#include <cstdlib>
#include <cmath>

/*
La classe Bestiole est la classe mère de toutes les Bestioles. On peut y définir:
         - AFF_SIZE: la taille des bestioles
         - MAX_VITESSE: la vitesse maximale des bestioles

         - CARAPACE, CAMOUFLAGE, NAEGOIRES, OREILLES et YEUX, les probabilités de posséder ces accessories/capteurs

On initialise aléatoirement les valeurs caractéristiques des accessoires et des capteurs dans le constructeur de chaque Bestioles
grâce à la fonction Rand.
*/

//Constantes propres à toutes les bestioles
const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
//const double      Bestiole::LIMITE_VUE = 30.;

int               Bestiole::next = 0;

T                *Bestiole::couleurCarap = new T[3];

//Accessoires
   //Probabilités d'avoir des accessoires
const double      Bestiole::CARAPACE=0.5;
const double      Bestiole::CAMOUFLAGE=0.7;
const double      Bestiole::NAGEOIRES=0.7;

//Capteurs
   //Probabilités d'avoir des capteurs
const double      Bestiole::OREILLES=0.7;
const double      Bestiole::YEUX=0.7;

//Prend en entrée 2 flottant et renvoie un flottant aléatoire entre les deux
double Rand(double min, double max){
   int m = ceil(min*100);
   int M = floor (max * 100);
   double rand = (double) (std::rand()%(M-m)+m);
   return rand/100;
}

//Constructeur
Bestiole::Bestiole( Milieu & milieu, Comportement * comp){
   this->comp=comp;

   //Accesoires
      //Nageoires
         //Valeur par défaut
   multiV=1;

   double b=Rand(0,1);
   if (b<NAGEOIRES){
      multiV=Rand(1, milieu.getVmax());
   }

      //Carapace
         //Valeurs par défaut
   double multiW=1;
   this->multiRedV=1;

   b=Rand(0,1);
   if (b<CARAPACE){
         //resistance
      multiW=Rand(1, milieu.getResmax());
         //reduction de la vitesse
      multiRedV=Rand(1, milieu.getRedV());
   }
      //Camouflage
         //Valeur par défaut
   camo = 0;

   b=Rand(0.,1.);
   if (b<CAMOUFLAGE){
      camo = Rand(milieu.getCamoMin(), milieu.getCamoMax());
   }
   
   //Capteur
      //Yeux
   angle=0;
   yeuxDist=0;
   yeuxDetec=0;

   b=Rand(0.,1.);
   if (b<YEUX){
         //angle
      angle = Rand(milieu.getAlphaMin(), milieu.getAlphaMax());
         //distance
      yeuxDist = Rand(milieu.getDistYeuxMin(), milieu.getDistYeuxMax());
         //Capacité de detection
      yeuxDetec = Rand(milieu.getDetecYeuxMin(), milieu.getDetecYeuxMax());
   }

      //Oreilles
         //Valeurs par défaut
   oreiDetec=0;
   oreiDist=0;

   b=Rand(0.,1.);
   if (b<OREILLES){
      oreiDetec = Rand(milieu.getDetecOreiMin(), milieu.getDetecOreiMax());
      oreiDist = Rand(milieu.getDistOreiMin(), milieu.getDistOreiMax());
   }

   //Probabilité de mourir lors d'une collision
   collision = 0.2/multiW;
   //Probabilité de Clonage d'une bestiole
   //clonage=0;
   clonage=0.002;

   identite = ++next;

   //Âge de la bestiole
   AGE_LIM = (int) std::rand()%(1000-300)+300;
   age = 0;

   //coordonnées, vitesse et orientation initiale
   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = (multiV*static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE)/multiRedV;
   //vitesse=MAX_VITESSE/2;

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

//Constructeur par copie
Bestiole::Bestiole( const Bestiole & b){  

   fuis=b.fuis;
   collision=b.collision;
   clonage=b.clonage;
   //Accessoires
   camo=b.camo;
   multiRedV=b.multiRedV;
   multiV=b.multiV;
   //capteurs
   //yeux
   angle=b.angle;
   yeuxDist = b.yeuxDist;
   yeuxDetec = b.yeuxDetec;

   //Oreilles
   oreiDetec = b.oreiDetec;
   oreiDist = b.oreiDist;



   identite = ++next;


   age=0;
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

//Destructeur
Bestiole::~Bestiole( void )
{

   delete[] couleur;

   //cout << "dest Bestiole" << endl;

}

//Opérateur d'assignation
Bestiole& Bestiole::operator=(const Bestiole& b){   
   if (this != &b){

      collision= b.collision;
      clonage=b.clonage;

      x=b.x;
      y=b.y;
      //Accessoires
      camo=b.camo;
      multiRedV=b.multiRedV;
      multiV=b.multiV;
      //capteurs
      //yeux
      angle=b.angle;
      yeuxDist = b.yeuxDist;
      yeuxDetec = b.yeuxDetec;

      //Oreilles
      oreiDetec = b.oreiDetec;
      oreiDist = b.oreiDist;

      age=0;
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
change la direction si la bestiole à dépasser les limites du milieu
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

   if (this->multiRedV>1){
         //Dessin de la carapace
      support.draw_circle(x,y,AFF_SIZE/4., couleurCarap, 10000000);
   }
   
   //if (this->angle!=0){
         //Dessin des yeux
     //support.draw_ellipse( xt+AFF_SIZE/2., yt, AFF_SIZE/8., AFF_SIZE/6., -orientation/M_PI*180., couleurCarap );
   //}

}

/*
Ré-ecriture de l'opérateur ==
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

//Setter
void Bestiole::setOrientation(double orientation){
   this->orientation=orientation;
}

void Bestiole::setVitesse(double vitesse){
   this->vitesse=vitesse;
}

//Getter   
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

bool Bestiole::hasCarap(){
   if (this->multiRedV>1){
      return true;
   }
   else {
      return false;
   }
}

bool Bestiole::hasCamo(){
   if (this->camo > 0){
      return true;
   }
   else {
      return false;
   }
}

//Est-ce que la bestiole a des nageoires ?
bool Bestiole::hasNageoires(){
   if (this->multiV > 1){
      return true;
   }
   else {
      return false;
   }
}

//La bestiole n'est pas une MultiBestiole
bool Bestiole::isMulti() const{
   return false;
}