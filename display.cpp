#include "display.hpp"

#include <thread>
#include <chrono>


void sequentiel(TypeCBZ archive){
    std::cout << "Ah" << endl;
    int compt = archive.nombre();
    for (int i = 0; i < compt; i++)
    {      
        std::cout << "On en est au fichier " << i << endl;
        Image image = archive.extractionImages(i);
        if (image.isValid() && image.columns() != 0 && image.rows() != 0) {
            std::cerr << "Image valide" << std::endl;
            image.resize("30%");

            image.display();
        }
        else
        {
        }
    }
    
}