#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>
#include <string>

#include "GLtexture.h"

using namespace std;

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLtexture getTexture(string texturePath);
private:
	map<string, GLtexture> textureMap;
};

#endif