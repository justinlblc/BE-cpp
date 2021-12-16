#include "Aquarium.h"
#include "Milieu.h"
/*
Classe Aquarium:

Cette classe s'occupe de simuler notre ecosystème via la méthode "run". Elle permet notamment l'initialisation du milieu en passant lui passant
tous les paramètres nécessaires à la simulation. On peut notamment y définir la largeur et longueur de la fenêtre. via les variablles:
            - screenWidth: longueur
            - screenHeight: largeur

*/

/*
Constructeur:
Input: Largeur, longueur du milieu, délai entre chaque pas de la simulation, 4 booléen (représentant les comportements choisis par l'utilsiateur,
dans l'ordre: Grégaire, Kamikaze, Peureuse et Prévoyante), puis les ' pointeurs vers les 4 comportements.
*/

Aquarium::Aquarium( int width, int height, int _delay, bool b1, bool b2, bool b3, bool b4, Gregaire * greg, Kamikaze * kami, Peureuse * peur, Prevoyante * prev ) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;

   //création du milieu
   flotte = new Milieu( width, height, b1, b2, b3, b4, greg, kami, peur, prev );
   assign( *flotte, "Simulation d'ecosysteme" );
   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}

//Destructeur
Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}

//Lancement de la simulation
void Aquarium::run( void )
{

   cout << "running Aquarium" << endl;

   while ( ! is_closed() )
   {

      // cout << "iteration de la simulation" << endl;

      if ( is_key() ) {
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ) close();
      }

      flotte->step();
      display( *flotte );

      wait( delay );

   }

}
