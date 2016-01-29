#include "LoadImage.h"

#include <SDL.h>
#include <SDL_image.h>

GLtexture LoadImage::load(string filePath)
{
	GLtexture tex = {};

	SDL_Surface* img = IMG_Load(filePath.c_str());

	if(img == NULL)
		cout << "Load Image file failed! :: " << filePath << endl;

	glGenTextures(1, &(tex.id));
	glBindTexture(GL_TEXTURE_2D, tex.id);

	GLenum formatTexture;
	switch(img->format->BytesPerPixel)
	{
	case 4:
		if(img->format->Rmask == 0x000000ff)
		{
			formatTexture = GL_RGBA;
		}else{
			formatTexture = GL_BGRA;
		}
		break;
	case 3:
		if(img->format->Rmask == 0x000000ff)
		{
			formatTexture = GL_RGB;
		}else{
			formatTexture = GL_BGR;
		}
		break;
	default:
		cout << "The Image not Truecolor." << endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, formatTexture, img->w, img->h, 0, formatTexture, GL_UNSIGNED_BYTE, img->pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	tex.width = img->w;
	tex.height = img->h;

	SDL_FreeSurface(img);
	img = NULL;
	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}