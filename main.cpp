#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Kamikaze.h"
#include "Prevoyante.h"
#include "Comportement.h"
#include "MultiBestiole.h"
#include <iostream>

using namespace std;

int main()
{

   Aquarium       ecosysteme( 640, 480, 30 );
   
   Gregaire greg;

   Peureuse peur;

   Kamikaze kami;

   Prevoyante prev;


for ( int i = 1; i <= 10; ++i ){
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), &greg));
   }
   ecosysteme.getMilieu().addMember( MultiBestiole(ecosysteme.getMilieu(), &greg, &kami, &peur, &prev));
   ecosysteme.run();


   return 0;
}
