//
// Created by ludo on 06/03/2022.
//

#include "ComportementKamikaze.h"
#include "math.h"
#include <cmath>
#include <iostream>

using namespace std;

ComportementKamikaze *ComportementKamikaze::comportement_kamikaze = nullptr;  // Instantiating the Pointer to the singleton

T* ComportementKamikaze::get_couleur(){
    return ComportementKamikaze::get_kamikaze()->couleur;
}

std::string ComportementKamikaze::get_type(){
    return ComportementKamikaze::get_kamikaze()->type;
}

ComportementKamikaze::ComportementKamikaze(void){
    couleur = new T[ 3 ];
    couleur[ 0 ] = 255;
    couleur[ 1 ] = 0;
    couleur[ 2 ] = 0;
    type = "kamikaze";
}

void ComportementKamikaze::action(Bestiole *actualBestiole, Milieu &monMilieu){
    std::vector<Bestiole*> mesVoisins = monMilieu.Voisins(*actualBestiole);
    if (mesVoisins.size() != 0){
        double x_proche = mesVoisins.front()->get_x(); // y de la bestiole la plus proche
        double y_proche = mesVoisins.front()->get_y(); // x de la bestiole la plus proche
        for ( std::vector<Bestiole*>::iterator it = mesVoisins.begin() ; it != mesVoisins.end() ; ++it ){
            double r_proche = std::pow(x_proche - actualBestiole->get_x(),2) + std::pow(y_proche - actualBestiole->get_y(),2);
            double r = std::pow((*it)->get_x() - actualBestiole->get_x(),2) + std::pow((*it)->get_y() - actualBestiole->get_y(),2);
            if ( r_proche > r ){            // calcul des x et y de la bestiole la plus proche
                x_proche = (*it)->get_x();
                y_proche = (*it)->get_y();   
            }
        } // calcul des distance pour le calcul des angles
        double H = std::sqrt(std::pow(x_proche - actualBestiole->get_x(),2) + std::pow(y_proche - actualBestiole->get_y(),2));
        double h = std::sqrt(std::pow(y_proche - actualBestiole->get_y(),2));
        double theta = asin(h/H); // calcul de l'orientation pour atteindre la target

        // adpatation des angles en fonction la position de la bestiole target

        if (-actualBestiole->get_y() < -y_proche){
            if (actualBestiole->get_x() < x_proche){
                actualBestiole->set_orientation(theta);
            } else {
                actualBestiole->set_orientation(M_PI - theta);
            }
        } else {
            if (actualBestiole->get_x() > x_proche){
                actualBestiole->set_orientation(M_PI + theta);
            } else {
                actualBestiole->set_orientation(-theta);
            }
        }
    }

}

ComportementKamikaze::~ComportementKamikaze()
{
    delete[] couleur;
}
