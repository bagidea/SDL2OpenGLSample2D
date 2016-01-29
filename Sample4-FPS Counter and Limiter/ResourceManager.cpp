#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

GLtexture ResourceManager::getTexture(string texturePath)
{
	return textureCache.getTexture(texturePath);
}