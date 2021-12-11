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


void lancerSimu(Aquarium ecosysteme, int gn, int Pn, int kn, int pn, Gregaire greg, Kamikaze kami, Peureuse peur, Prevoyante prev){
   //Grégaire
   for (int i = 0;i<gn;i++){
         ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), &greg));   
   }

   //Peureuse
   for (int i = 0;i<Pn;i++){
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), &peur));
   }

   //Kamikaze
   for (int i = 0;i<kn;i++){
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), &kami));
   }

   //Prévoyante
   for (int i = 0;i<pn;i++){
      ecosysteme.getMilieu().addMember( Bestiole(ecosysteme.getMilieu(), &prev));
   }
   ecosysteme.run();
   }

int main()
{
   
   Gregaire greg;

   Peureuse peur;

   Kamikaze kami;

   Prevoyante prev;

   int n = 0;
   int g;
   cout<<"Pourcentage de Grégaire? ";
   cin >> g;
   if (g!=0){
      n++;
   }

   int k;
   cout<<"Pourcentage de Kamikaze? ";
   cin >> k;
   if (k!=0){
      n++;
   }

   int P;
   cout<<"Pourcentage de Peureuse? ";
   cin >> P;
   if (P!=0){
      n++;
   }

   int p;
   cout<<"Pourcentage de Prévoyante? ";
   cin >> p;
   if (p!=0){
      n++;
   }

   int nb;
   cout << "Nombre de bestioles au total? ";
   cin >> nb;

  
   int gn = ceil(nb*g/100);
   int kn = ceil(nb*k/100);
   int Pn = ceil(nb*P/100);
   int pn = ceil(nb*p/100);
   
   int largeur = 960;
   int longueur = 1280;



   Aquarium       ecosysteme( longueur, largeur, 30, true, true, true, true, greg, kami, peur, prev);

   ecosysteme.getMilieu().addMember(MultiBestiole(ecosysteme.getMilieu(), &greg, &kami, &peur, &prev));
   lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);

   return 0;
}
