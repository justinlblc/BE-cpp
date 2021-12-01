#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
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

   for ( int i = 1; i <= 10; ++i )
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), gregaire));
   ecosysteme.run();


   return 0;
}
