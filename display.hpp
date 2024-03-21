// Archive.hpp
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include <vector>
#include <string>
#include <zip.h>
#include "adj.hpp"
#include "archive.hpp"
#include <Magick++.h>

using namespace std;
using namespace Magick;

void sequentiel(TypeCBZ archive);

void asynchrone(TypeCBZ archive);

#endif