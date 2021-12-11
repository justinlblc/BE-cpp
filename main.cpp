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
   
   Gregaire greg;

   Peureuse peur;

   Kamikaze kami;

   Prevoyante prev;

   int g;
   cout<<"Pourcentage de Grégaire? ";
   cin >> g;

   int P;
   cout<<"Pourcentage de Peureuse? ";
   cin >> P;

   int k;
   cout<<"Pourcentage de Kamikaze? ";
   cin >> k;

   int p;
   cout<<"Pourcentage de Kamikaze? ";
   cin >> p;

   int nb;
   cout << "Nombre de bestioles au total? ";
   cin >> nb;

   

Aquarium       ecosysteme( 640, 480, 30 );


//
for ( int i = 1; i <= 5; ++i ){
   ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), &greg));
}
   ecosysteme.getMilieu().addMember( MultiBestiole(ecosysteme.getMilieu(), &greg, &kami, &peur, &prev));
   ecosysteme.run();


   return 0;
}
