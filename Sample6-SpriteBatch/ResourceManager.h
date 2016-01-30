#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>

#include "TextureCache.h"
#include "GLtexture.h"

using namespace std;

class ResourceManager
{
public:
	static GLtexture getTexture(string texturePath);
private:
	static TextureCache textureCache;
};

#endif