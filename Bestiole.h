#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include  "Comportement.h"
#include "ComportementGregaire.h"
#include "ComportementKamikaze.h"
#include "ComportementPrevoyante.h"
#include "ComportementPeureuse.h"
#include <iostream>

using namespace std;


class Milieu;


class Bestiole
{

private :
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;
   static int              next;
   static int              NB_COMPORTEMENT;

private :
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   bool              comportement_multiple;
   Comportement      * comportement;



private :
   void bouge( int xLim, int yLim );

public :                                           // Forme canonique :
   Bestiole(const std::string comportement);                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies               
   Bestiole();
   ~Bestiole( void )=default;                              // Destructeur
                                                   // Operateur d'affectation binaire par defaut
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( const Bestiole & b ) const;

   void initCoords( int xLim, int yLim );
   const bool estMultiple();
   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );
   Bestiole& operator=(const Bestiole& b);
   void randomComportement();
   void changerComportement();
   void setComportement(int comprotement);
   void meurt(Milieu & monMilieu, int nbBestioles);
};


#endif
