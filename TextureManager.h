#pragma once
#include <SDL.h>

class TextureManager
{
public:
	static TextureManager &getInstance() {
		static TextureManager manager;
		return manager;
	}

private:
	TextureManager(TextureManager const &);
	TextureManager &operator=(TextureManager const &);
	TextureManager();
	~TextureManager();

public:
	void init(SDL_Renderer *renderer);
	void cleanUp();

	SDL_Texture *mDragonFlyTexture;
	SDL_Rect mDragonFlyTextureRect;

	SDL_Texture *mRedFireballTexture;
	SDL_Rect mRedFireballTextureRect;
	SDL_Texture *mBlueFireballTexture;
	SDL_Rect mBlueFireballTextureRect;
	SDL_Texture *mPinkFireballTexture;
	SDL_Rect mPinkFireballTextureRect;

	SDL_Texture *mChickenFlyTexture;
	SDL_Rect mChickenFlyTextureRect;
	SDL_Texture *mChickenHitTexture;
	SDL_Rect mChickenHitTextureRect;
	SDL_Texture *mDuckFlyTexture;
	SDL_Rect mDuckFlyTextureRect;
	SDL_Texture *mDuckHitTexture;
	SDL_Rect mDuckHitTextureRect;
	SDL_Texture *mGreenFlyTexture;
	SDL_Rect mGreenFlyTextureRect;
	SDL_Texture *mGreenHitTexture;
	SDL_Rect mGreenHitTextureRect;
	SDL_Texture *mMonsterFlyTexture;
	SDL_Rect mMonsterFlyTextureRect;
	SDL_Texture *mMonsterHitTexture;
	SDL_Rect mMonsterHitTextureRect;

	SDL_Texture *gameOverTexture;
	SDL_Rect gameOverRect;
};

