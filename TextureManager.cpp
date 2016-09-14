#include "TextureManager.h"

#include "Sprite.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	cleanUp();
}

void TextureManager::cleanUp() {
	SDL_DestroyTexture(mDragonFlyTexture);
	mDragonFlyTexture = nullptr;
	SDL_DestroyTexture(mRedFireballTexture);
	mRedFireballTexture = nullptr;
	SDL_DestroyTexture(mBlueFireballTexture);
	mBlueFireballTexture = nullptr;
	SDL_DestroyTexture(mPinkFireballTexture);
	mPinkFireballTexture = nullptr;

}

void TextureManager::init(SDL_Renderer * renderer)
{
	mDragonFlyTextureRect = { 0, 0, 0, 0};
	mDragonFlyTexture = loadTexture("dragon_fly.bmp", renderer, &mDragonFlyTextureRect.w, &mDragonFlyTextureRect.h);

	mRedFireballTextureRect = { 0, 0, 0, 0 };
	mRedFireballTexture = loadTexture("fireball_red.bmp", renderer, &mRedFireballTextureRect.w, &mRedFireballTextureRect.h);
	mBlueFireballTextureRect = { 0, 0, 0, 0 };
	mBlueFireballTexture = loadTexture("fireball_blue.bmp", renderer, &mBlueFireballTextureRect.w, &mBlueFireballTextureRect.h);
	mPinkFireballTextureRect = { 0, 0, 0, 0 };
	mPinkFireballTexture = loadTexture("fireball_pink.bmp", renderer, &mPinkFireballTextureRect.w, &mPinkFireballTextureRect.h);

	mChickenFlyTextureRect = { 0,0,0,0 };
	mChickenFlyTexture = loadTexture("chicken_fly.bmp", renderer, &mChickenFlyTextureRect.w, &mChickenFlyTextureRect.h);
	mChickenHitTextureRect = { 0,0,0,0 };
	mChickenHitTexture = loadTexture("chicken_hit.bmp", renderer, &mChickenHitTextureRect.w, &mChickenHitTextureRect.h);
	mDuckFlyTextureRect = { 0,0,0,0 };
	mDuckFlyTexture = loadTexture("duck_fly.bmp", renderer, &mDuckFlyTextureRect.w, &mDuckFlyTextureRect.h);
	mDuckHitTextureRect = { 0,0,0,0 };
	mDuckHitTexture = loadTexture("duck_hit.bmp", renderer, &mDuckHitTextureRect.w, &mDuckHitTextureRect.h);
	mGreenFlyTextureRect = { 0,0,0,0 };
	mGreenFlyTexture = loadTexture("green_fly.bmp", renderer, &mGreenFlyTextureRect.w, &mGreenFlyTextureRect.h);
	mGreenHitTextureRect = { 0,0,0,0 };
	mGreenHitTexture = loadTexture("green_hit.bmp", renderer, &mGreenHitTextureRect.w, &mGreenHitTextureRect.h);
	mMonsterFlyTextureRect = { 0,0,0,0 };
	mMonsterFlyTexture = loadTexture("monster_fly.bmp", renderer, &mMonsterFlyTextureRect.w, &mMonsterFlyTextureRect.h);
	mMonsterHitTextureRect = {0,0,0,0};
	mMonsterHitTexture = loadTexture("monster_hit.bmp", renderer, &mMonsterHitTextureRect.w, &mMonsterHitTextureRect.h);

	gameOverRect = { 0,0,0,0 };
	gameOverTexture = loadTexture("gameOver.bmp", renderer, &gameOverRect.w, &gameOverRect.h);
}
