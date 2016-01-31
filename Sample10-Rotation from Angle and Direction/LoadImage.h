#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include <iostream>
#include <string>

#include "GLtexture.h"

using namespace std;

class LoadImage
{
public:
	static GLtexture load(string filePath);
};

#endif