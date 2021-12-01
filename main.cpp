#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
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

   Prevoyante prev;
   Prevoyante * prevoyante = &prev;

   
   for ( int i = 1; i <= 10; ++i ){
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), gregaire));
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), peureuse));
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), kamikaze));
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), prevoyante));
      
   }
   ecosysteme.run();


   return 0;
}
