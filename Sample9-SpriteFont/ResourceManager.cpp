#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;
FontCache ResourceManager::fontCache;

GLtexture ResourceManager::getTexture(string texturePath)
{
	return textureCache.getTexture(texturePath);
}

TTF_Font* ResourceManager::getFont(string fontPath, int size)
{
	return fontCache.getFont(fontPath, size);
}