#include "FontCache.h"

FontCache::FontCache()
{
}

FontCache::~FontCache()
{
}

TTF_Font* FontCache::getFont(string fontPath, int size)
{
	auto mit = fontMap.find(fontPath.c_str()+size);
	
	if(mit == fontMap.end())
	{
		TTF_Font* newFont = TTF_OpenFont(fontPath.c_str(), size);

		if(newFont == NULL)
			cout << "TTF open font fail" << endl;

		fontMap.insert(make_pair(fontPath.c_str()+size, newFont));
		
		cout << "new Font." << endl;
		return newFont;
	}

	cout << "Load Font." << endl;
	return mit->second;
}