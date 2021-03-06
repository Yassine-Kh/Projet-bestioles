//
// Created by yassine on 05/03/2022.
//

#include "ComportementGregaire.h"


ComportementGregaire *ComportementGregaire::comportement_gregaire = nullptr;  // Instantiating the Pointer to the singleton

T* ComportementGregaire::get_couleur(){
    return ComportementGregaire::get_gregaire()->couleur;
}
std::string ComportementGregaire::get_type(){
    return ComportementGregaire::get_gregaire()->type;
}
ComportementGregaire::ComportementGregaire(void){
    couleur = new T[ 3 ];
    couleur[ 0 ] = 0;
    couleur[ 1 ] = 255;
    couleur[ 2 ] = 0;
    type = "gregaire";
}

void ComportementGregaire::action(Bestiole *actualBestiole, Milieu &monMilieu){
    std::vector<Bestiole*> mesVoisins = monMilieu.Voisins(*actualBestiole);
    if (mesVoisins.size() != 0){
        double dir_moy = 0.; // direction moyenne des bestioles voisines
        for ( std::vector<Bestiole*>::iterator it = mesVoisins.begin() ; it != mesVoisins.end() ; ++it ){
            dir_moy += ((*it)->get_orientation()); // calcul de l'orientation moyenne
        }

        actualBestiole->set_orientation(dir_moy/(mesVoisins.size())); // changement d'orientation
    }
    else{
        actualBestiole->set_orientation(actualBestiole->get_orientation());
    }
}

ComportementGregaire::~ComportementGregaire()
{
    delete[] couleur;
}