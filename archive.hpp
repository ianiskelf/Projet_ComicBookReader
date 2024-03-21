// Archive.hpp
#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <zip.h>
#include "adj.hpp"
#include <Magick++.h>

// On utilise la librairie #include <Magick++.h> qui va nous permettre de manipuler plus facilement les images. 
// Il s'agit 

// ========== ARCHIVE ==========
// On définit une classe archive pour les manipulations de base sur les archives
class Archive {
protected:
    std::string const nom_archive;

public:
    Archive(std::string n);
    ~Archive();                             
    virtual void ouvrir() = 0;                      // Ouverture de l'archive
    virtual std::vector<std::string> liste() = 0;   // Liste des noms des fichiers
    bool estImage(const std::string& filename);    
};

// ========== CBZ ==========
// Une classe dérivée de la classe Archive pour traîter les .cbz
class TypeCBZ : public Archive {
private:
    zip* archive;                                   // Un pointeur vers l'archive à ouvrir

public:
    TypeCBZ(std::string n);                         // Le constructeur propre à cette classe
    void ouvrir() override;                         // Ouverture de l'archive
    int nombre();                                  // Nombre de fichiers
    std::vector<std::string> liste() override;      // Liste des noms des fichiers
    Magick::Image extractionImages(int i);          // Retourne le i-ème fichier de l'archive si c'est une image 
};

// ========== CBR ==========
// Une classe dérivée de la classe Archive pour traîter les .cbr
class TypeCBR : public Archive {
private:
    zip* archive;                                   // Un pointeur vers l'archive à ouvrir

public:
    TypeCBR(std::string n);                         // Le constructeur propre à cette classe
    void ouvrir() override;                         // Ouverture de l'archive
};

#endif // ARCHIVE_HPP