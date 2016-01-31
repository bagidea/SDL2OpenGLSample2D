#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <map>
#include <iostream>
#include <string>
#include <SDL_ttf.h>

using namespace std;

class FontCache
{
public:
	FontCache();
	~FontCache();

	TTF_Font* getFont(string fontPath, int size);
private:
	map<string, TTF_Font*> fontMap;
};

#endif