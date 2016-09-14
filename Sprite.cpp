#include "Sprite.h"
#include <iostream>

SDL_Texture *loadTexture(std::string const &path, SDL_Renderer *rend, int *w, int *h) {
	//	Load pixels into RAM from disk
	SDL_Surface *surf = SDL_LoadBMP(path.c_str());
	
	if (surf == nullptr) {
		std::cout << "Error loading image from file: " << std::endl <<
			SDL_GetError() << std::endl;
		return nullptr;
	}
	//Set the color key for transparency
	int ck = SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255,0,255));
	// Move pixels from CPU RAM to GPU RAM
	SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
	if (tex == nullptr) {
		std::cout << "Error creating texture: " << std::endl <<
			SDL_GetError() << std::endl;
		//No return here since we want to free the pixels first.
	}
	if(w != nullptr) {
		*w = surf->w;
	}
	if (h != nullptr) {
		*h = surf->h;
	}
	//Surface is no longer needed since our pixels are now on the GPU
	SDL_FreeSurface(surf);

	return tex;
}

Sprite::Sprite(SDL_Texture *tex, SDL_Rect srcRect)
 : mTexture(tex), mSrcRect(srcRect)
{
}

//This is not strictly speaking necessary unless
// we are doing funky inplace deletions, which
// we aren't.
Sprite::~Sprite()
{
	mTexture = nullptr;
}

void Sprite::draw(SDL_Renderer * renderer, SDL_Rect dst) const
{
	SDL_RenderCopy(renderer, mTexture, &mSrcRect, &dst);
}

void Sprite::draw(SDL_Renderer * renderer, SDL_Rect dst, float angle) const
{
	SDL_RenderCopyEx(renderer, mTexture, &mSrcRect, &dst, angle, nullptr, SDL_FLIP_NONE);
}
