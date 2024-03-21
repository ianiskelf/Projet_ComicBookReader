#include <iostream>
#include <vector>
#include <string>

#include "archive.hpp"
#include "display.hpp"
#include <Magick++.h>

using namespace std;
using namespace Magick;

int main(int argc, char* argv[]) { // Par exemple "The Smurfs and Friends vol. 01 (2015) GetComics.INFO.cbz"
    if (argc >= 2) {

    std::string s = argv[1];
    TypeCBZ fich = TypeCBZ(s);
    fich.ouvrir();
    fich.nombre();
    fich.liste();
    // Il faut initialiser ImageMagick avant de l'utiliser
    InitializeMagick(nullptr);

    sequentiel(fich);}
    else {
        std::cout << "Pas d'arguments donnés en ligne de commande" << std::endl;
    }
    
    return 0;
}