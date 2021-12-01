#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Comportement.h"
#include <iostream>

using namespace std;


int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );
   
   Gregaire greg;
   Gregaire * gregaire = &greg;

   Peureuse peur;
   Peureuse * peureuse = &peur;

   Kamikaze kami;
   Kamikaze * kamikaze = &kami;
   
   for ( int i = 1; i <= 2; ++i )
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), kamikaze));
   ecosysteme.run();


   return 0;
}
