#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>

#include "TextureCache.h"
#include "FontCache.h"
#include "GLtexture.h"

using namespace std;

class ResourceManager
{
public:
	static GLtexture getTexture(string texturePath);
	static TTF_Font* getFont(string fontPath, int size);
private:
	static TextureCache textureCache;
	static FontCache fontCache;
};

#endif