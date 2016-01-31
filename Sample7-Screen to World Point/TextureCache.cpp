#include "TextureCache.h"

#include "LoadImage.h"

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}


GLtexture TextureCache::getTexture(string texturePath)
{
	auto mit = textureMap.find(texturePath);
	
	if(mit == textureMap.end())
	{
		GLtexture newTexture = LoadImage::load(texturePath);

		textureMap.insert(make_pair(texturePath, newTexture));
		
		cout << "new Texture." << endl;
		return newTexture;
	}

	cout << "Load Texture." << endl;
	return mit->second;
}