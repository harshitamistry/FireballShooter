#include "WaveEntity.h"

#include "TextureManager.h"
#include "AnimatedSprite.h"
#include "BirdEntity.h" 
#include "FireBallEntity.h"
#include <time.h>   

#include<math.h>




WaveEntity::WaveEntity(float x, float y, SpawnEntity *spawn, DragonEntity *dragon, BIRDTYPE type,int size)
	: Entity(0, 0, 0, 0)
{
	this->size = size;
	this->spawner = spawn;
	this->dragon = dragon;
	this->type = type;
	float height = 100;
	AnimatedSprite* as;
	int frameTime = 100;
	srand(2 * time(NULL));
	SDL_Texture* arr[4] = { TextureManager::getInstance().mChickenFlyTexture,TextureManager::getInstance().mGreenFlyTexture,TextureManager::getInstance().mDuckFlyTexture,TextureManager::getInstance().mMonsterFlyTexture };
	SDL_Rect arr2[4] = { TextureManager::getInstance().mChickenFlyTextureRect,TextureManager::getInstance().mGreenFlyTextureRect,TextureManager::getInstance().mDuckFlyTextureRect,TextureManager::getInstance().mMonsterFlyTextureRect };
	if (size == 1) {
		height = rand() % mScreenHeight;
		//std::cout << height << std::endl;
		as = new AnimatedSprite(TextureManager::getInstance().mChickenFlyTexture, TextureManager::getInstance().mChickenFlyTextureRect, 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
		mEntities.push_back(new BirdEntity(Entity::mScreenWidth, height, as, spawn, dragon, type,1));
	}
	else
	{
		for (int i = 0;i < size;i++) {
			int k = rand() % 4;
			as = new AnimatedSprite(arr[k], arr2[k], 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
			mEntities.push_back(new BirdEntity(Entity::mScreenWidth, height, as, spawn, dragon, type,(k%2==0)?2:1));
			height += mScreenHeight / size;
		}
	}
}

WaveEntity::~WaveEntity()
{

	for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		delete (*it);
	}
	mEntities.clear();
}

void WaveEntity::update(int delta, Uint8 const * keys)
{
	for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		(*it)->update(delta, keys);
	}
}
void WaveEntity::draw(SDL_Renderer * renderer) const
{
	for (std::list<Entity *>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		(*it)->draw(renderer);
	}

}

bool WaveEntity::message(MessageID id, void * data)
{
	if (id == MessageID::STOP_ANIMATION) {
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end();it++ ) {
			(*it)->message(id,data);
		}
		return true;
	}
	else if (id == MessageID::START_ANIMATION) {
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
			(*it)->message(id, data);
		}
		return true;
	}
	else if (id == MessageID::REMOVE) {
		bool result=false;
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
			result= result || (*it)->message(id, data);
		}
		return result;
	}
	else if (id == MessageID::WAVE) {
		return true;
	}
	else if (id == MessageID::CHECKBIRDS) {
		FireBallEntity* fb = (FireBallEntity*)data;
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end();) {
			BirdEntity* bdd = (BirdEntity*)(*it);
			if (SpawnEntity::checkCollision(fb, (*it))) {
				//std::cout << bdd->hit;
				bdd->hit--;
				if (bdd->hit == 0) {
					it = mEntities.erase(it);
					delete bdd;
				}
				
				else
					it++;
			}
			else
				it++;
		}
		return true;
	}
	else if (id == MessageID::CHECKDRAGON) {
		DragonEntity* fb = (DragonEntity*)data;
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end();it++) {
			if (SpawnEntity::checkCollision(fb, (*it))) {
				return true;
			}
		}
		return false;
	}
	if (id == MessageID::SCREEN_SIZE) {
		//Code here to handle the screen being resized.
		return true;
	}
	//Call to parent class.

	return Entity::message(id, data);
}