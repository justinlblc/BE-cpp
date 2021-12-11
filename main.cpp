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

//fonction de lancement de simulation
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

   Kamikaze kami;

   Peureuse peur;

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
   cout<<"Nombre: "<<n<<endl;
  
   int gn = ceil(nb*g/100);
   int kn = ceil(nb*k/100);
   int Pn = ceil(nb*P/100);
   int pn = ceil(nb*p/100);
   
   int largeur = 960;
   int longueur = 1280;


   // cas où toutes les bestioles
   if (n==4){
      Aquarium       ecosysteme( longueur, largeur, 30, true, true, true, true, greg, kami, peur, prev);
      lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
   }
   else if (n==3){
      if (g!=0 && k!=0 && P!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, true, true, true, false, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (g!=0 && k!=00 && p!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, true, true, false, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if(g!=0 && P!=0 && p!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, true, false, true, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else {
         Aquarium       ecosysteme( longueur, largeur, 30, false, true, true, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      
   }
   //Si deux types de bestioles
   else if (n==2){
      if (g!=0 && k!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, true, true, false, false, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (g!=0 && P!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, true, false, true, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (g!=0 && p!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, true, false, false, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (k!=0 && P!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, false, true, true, false, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (k!=0 && p!=0){
         Aquarium       ecosysteme( longueur, largeur, 30, false, true, false, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else {
         Aquarium       ecosysteme( longueur, largeur, 30, false, false, true, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }

   }

   //cas où un seul type de bestiole
   else {
      if (g!=0){
         cout<<"Que Grégaire"<<endl;
         Aquarium       ecosysteme( longueur, largeur, 30, true, false, false, false, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (k!=0){
         cout<<"Que Kamikaze"<<endl;
         Aquarium       ecosysteme( longueur, largeur, 30, false, true, false, false, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else if (P!=0){
         cout<<"Que Peureuse"<<endl;
         Aquarium       ecosysteme( longueur, largeur, 30, false, false, true, false, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
      else{
         cout<<"Que Prévoyante"<<endl;
         Aquarium       ecosysteme(longueur, largeur, 30, false, false, false, true, greg, kami, peur, prev);
         lancerSimu(ecosysteme, gn, Pn, kn, pn, greg, kami, peur, prev);
      }
   return 0;
   }
}