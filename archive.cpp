#include "archive.hpp"

using namespace std;
using namespace Magick;

// ========== ARCHIVE ==========
// Fonctions communes à tout le monde
Archive::Archive(std::string n) : nom_archive(n) {
    std::cout << "Création Archive : " << this << std::endl;
}

Archive::~Archive() {
    std::cout << "Destruction Archive : " << this << std::endl;
}

bool Archive::estImage(const std::string& filename) {
    return (extension(filename, ".png") || extension(filename, ".jpg") || extension(filename, ".jpeg") || extension(filename, ".bmp"));
}

// ========== CBZ ==========
// Définition des fonctions propre à la classe dérivée en fonction des spécificités des .cbz
TypeCBZ::TypeCBZ(std::string n) : Archive(n) {}     // Constructeur

void TypeCBZ::ouvrir() {
    std::cout << "Ouverture d'un fichier ZIP : " << nom_archive << std::endl;

    archive = zip_open(nom_archive.c_str(), 0, NULL);

    if (!archive) {
        std::cerr << "Échec de l'ouverture du fichier zip" << std::endl;
        return;
    }
}

int TypeCBZ::nombre() {
    if (!archive) {
        std::cerr << "Pas d'archive ouverte" << std::endl;
        return 0;
    }
    int numFiles = zip_get_num_files(archive);
    std::cout << "On a " << numFiles << " fichiers dans l'archive" << std::endl;
    return numFiles;
}

std::vector<std::string> TypeCBZ::liste() {
    std::vector<std::string> files;
    int numFiles = zip_get_num_files(archive);

    for (int i = 0; i < numFiles; ++i) {
        struct zip_stat fileInfo;
        zip_stat_init(&fileInfo);

        if (zip_stat_index(archive, i, 0, &fileInfo) == 0) {
            std::cout << "Nom du fichier " << i << " : " << fileInfo.name << std::endl;
            files.push_back(fileInfo.name);
        }
    }
    return files;
}

// Une fonction pour extraire la ième image du fichier. 
Magick::Image TypeCBZ::extractionImages(int i) {
    if (!archive) {
        std::cerr << "Pas d'archive ouverte" << std::endl;
        return Image();
    }

    // Trouver le fichier d'indice 1
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat_index(archive, i, 0, &st);
    zip_file *file = zip_fopen_index(archive, i, 0);
    if (!file) {
        cerr << "Echec de l'ouverture du premier fichier du zip." << endl;
        zip_close(archive);
        return Image();
    }

    std::string nomfich = st.name;

    if (!estImage(nomfich)){
        return Image();
    }

    // On lit les données de l'image
    char *data = new char[st.size];
    zip_fread(file, data, st.size);
    zip_fclose(file);

    // Et on les charge avec ImageMagick
    Blob blob(data, st.size);
    if (blob.length() == 0) {
        cerr << "Echec lecture données image" << endl;
        delete[] data;
        zip_close(archive);
        return Image();
    }

    Image image = Image();
    try {
        image.read(blob);
    } catch (Exception &error) {
        cerr << "Echec lecture image : " << error.what() << endl;
        delete[] data;
        zip_close(archive);
        return Image();
    }

    delete[] data;

    return image;
}

// ========== CBR ==========
// Définition des fonctions propre à la classe dérivée en fonction des spécificités des .cbr
// Malheureusement, traîter des .rar est un peu plus compliqué que les .zip
// Le seul moyen que j'ai trouvé est d'utiliser des commandes système
// Par exemple, grâce à 7z ou unrar

// Notons que 7z ne différencie pas les cbz et les cbr
// J'ai donc fait le choix d'utiliser unrar pour illustrer les différences entre TypeCBR et TypeCBZ

TypeCBR::TypeCBR(std::string n) : Archive(n) {} // Constructeur

void TypeCBR::ouvrir() {
    std::cout << "Ouverture d'un fichier RAR : " << nom_archive << std::endl;

    // On stocke tout dans un fichier temp_folder 
    // Il faut qu'il existe déjà, la commande ne parvient pas à le créer elle-même

    std::string command = "unrar x \"" + nom_archive + "\" -o" + "temp_folder";
    int ret = std::system(command.c_str());
    if (ret != 0) {
        std::cerr << "Échec de l'ouverture du fichier RAR" << std::endl;
        return;
    }
}
