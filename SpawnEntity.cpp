#include "SpawnEntity.h"

#include "TextureManager.h"
#include "AnimatedSprite.h"
#include "GenericEntity.h"
#include "FireBallEntity.h"
#include "WaveEntity.h"
#include "Game.h"


SpawnEntity::SpawnEntity()
	: Entity(0,0,0,0)
{
	Vector2f pos(10.0f, 400.0f);
	int frameTime = 100;
	AnimatedSprite *as = new AnimatedSprite(TextureManager::getInstance().mDragonFlyTexture, TextureManager::getInstance().mDragonFlyTextureRect, 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
	dragon = new DragonEntity(pos.x, pos.y, as);
	mEntities.push_back(dragon);
	pos.x += 200;
	/*
	as = new AnimatedSprite(TextureManager::getInstance().mRedFireballTexture, TextureManager::getInstance().mRedFireballTextureRect, 6, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 200;
	as = new AnimatedSprite(TextureManager::getInstance().mBlueFireballTexture, TextureManager::getInstance().mBlueFireballTextureRect, 6, frameTime, AnimationDirection::REVERSE, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 200;
	
	as = new AnimatedSprite(TextureManager::getInstance().mPinkFireballTexture, TextureManager::getInstance().mPinkFireballTextureRect, 6, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));

	pos.x = 10;
	pos.y += 150;
	*/
	
	//as = new AnimatedSprite(TextureManager::getInstance().mChickenFlyTexture, TextureManager::getInstance().mChickenFlyTextureRect, 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
	//mEntities.push_back(new WaveEntity(Entity::mScreenWidth, Entity::mScreenHeight/2,this,dragon,BIRDTYPE::SINEBIRD,1));
	//pos.x += 150;
	/*as = new AnimatedSprite(TextureManager::getInstance().mDuckFlyTexture, TextureManager::getInstance().mDuckFlyTextureRect, 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
	mEntities.push_back(new BirdEntity(Entity::mScreenWidth, Entity::mScreenHeight / 2, as, this,dragon,BIRDTYPE::TOPLAYERBIRD));
	pos.x += 150;
	
	as = new AnimatedSprite(TextureManager::getInstance().mGreenFlyTexture, TextureManager::getInstance().mGreenFlyTextureRect, 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 150;
	as = new AnimatedSprite(TextureManager::getInstance().mMonsterFlyTexture, TextureManager::getInstance().mMonsterFlyTextureRect, 4, frameTime, AnimationDirection::FORWARD, AnimationType::BOUNCE, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 150;

	frameTime = 200;
	pos.x = 10;
	pos.y += 150;
	as = new AnimatedSprite(TextureManager::getInstance().mChickenHitTexture, TextureManager::getInstance().mChickenHitTextureRect, 2, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 150;
	as = new AnimatedSprite(TextureManager::getInstance().mDuckHitTexture, TextureManager::getInstance().mDuckHitTextureRect, 2, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 150;
	as = new AnimatedSprite(TextureManager::getInstance().mGreenHitTexture, TextureManager::getInstance().mGreenHitTextureRect, 2, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 150;
	as = new AnimatedSprite(TextureManager::getInstance().mMonsterHitTexture, TextureManager::getInstance().mMonsterHitTextureRect, 2, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
	mEntities.push_back(new GenericEntity(pos.x, pos.y, as));
	pos.x += 150;
	*/
}

SpawnEntity::~SpawnEntity()
{
	for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		delete (*it);
	}
	mEntities.clear();
}

bool SpawnEntity::checkCollision(Entity* it1, Entity* it2) {
	bool result = false;
	result = result || (((it1->getRect().x + it1->getRect().w >= it2->getRect().x && it1->getRect().x < it2->getRect().x) || (it2->getRect().x + it2->getRect().w >= it1->getRect().x && it2->getRect().x < it1->getRect().x)) && ((it1->getRect().y >it2->getRect().y && it1->getRect().y < it2->getRect().y + it2->getRect().h) || (it2->getRect().y >it1->getRect().y && it2->getRect().y < it1->getRect().y + it1->getRect().h)));
	return result;
}

void SpawnEntity::update(int delta, Uint8 const * keys)
{
	if (status) {
		return;
	}
	lastwavetime += delta;

	if (lastwavetime > 3000) {
		int k = 0;
		if (wavenumber == 1) {
			k = 1;
		}
		else if (wavenumber == 2) {
			k = 2;
		}
		if (wavenumber > 2) {
			k = rand() % 4;
			if (k == 2)
				k = 3;
		}
		wavenumber++;
		mEntities.push_back(new WaveEntity(Entity::mScreenWidth, Entity::mScreenHeight / 2, this, dragon, (BIRDTYPE)k, (k==0)?3:2));
		lastwavetime = 0;
	}

	

	for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		if ((*it)->message(MessageID::WAVE, nullptr)) {
			for (std::list<Entity *>::iterator it2 = mEntities.begin(); it2 != mEntities.end(); it2++) {
				if ((*it2)->message(MessageID::DRAGON, nullptr)) {

					if ((*it)->message(MessageID::CHECKDRAGON, (*it2))) {
						status = true;
					}
					if (status) {
						it2 = mEntities.erase(it2);
						break;
					}
					else
						it2++;
				}
			}
		}
		else if ((*it)->message(MessageID::FIREBALL, nullptr)) {
			for (std::list<Entity *>::iterator it2 = mEntities.begin(); it2 != mEntities.end(); it2++) {
				if ((*it2)->message(MessageID::WAVE, nullptr)) {
					(*it2)->message(MessageID::CHECKBIRDS, (*it));
				}
			}
		}

		if (status) {
			break;
		}
	}


	if (keys[SDL_SCANCODE_SPACE] == 1 && fireBallTime > 500) {
		int frameTime = 100;
		AnimatedSprite *as;
		fireBallTime = 0;
		if (fireBallCounter == 0) {
			as = new AnimatedSprite(TextureManager::getInstance().mRedFireballTexture, TextureManager::getInstance().mRedFireballTextureRect, 6, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
			mEntities.push_back(new FireBallEntity(dragon->getRect().x + dragon->getRect().w, dragon->getRect().y, as, this));
			fireBallCounter = 1;
		}
		else if (fireBallCounter == 1) {
			as = new AnimatedSprite(TextureManager::getInstance().mBlueFireballTexture, TextureManager::getInstance().mBlueFireballTextureRect, 6, frameTime, AnimationDirection::REVERSE, AnimationType::LOOP, true);
			mEntities.push_back(new FireBallEntity(dragon->getRect().x + dragon->getRect().w, dragon->getRect().y, as, this));
			fireBallCounter = 2;
		}
		else if (fireBallCounter == 2) {
			as = new AnimatedSprite(TextureManager::getInstance().mPinkFireballTexture, TextureManager::getInstance().mPinkFireballTextureRect, 6, frameTime, AnimationDirection::FORWARD, AnimationType::LOOP, true);
			mEntities.push_back(new FireBallEntity(dragon->getRect().x + dragon->getRect().w, dragon->getRect().y, as, this));
			fireBallCounter = 0;
		}

	}
	else {
		fireBallTime += delta;
	}

	//Keyboard input can be handled here.
	if (keys[SDL_SCANCODE_O]) {
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
			(*it)->message(MessageID::START_ANIMATION, nullptr);
		}
	}
	if (keys[SDL_SCANCODE_P]) {
		for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
			(*it)->message(MessageID::STOP_ANIMATION, nullptr);
		}
	}

	Entity* toremove = nullptr;
	for (std::list<Entity *>::iterator it = mEntities.begin(); it != mEntities.end(); ) {
		(*it)->update(delta, keys);
		if ((*it)->message(MessageID::REMOVE, nullptr)) {
			toremove = (Entity*)*it;
			it = mEntities.erase(it);
			delete toremove;

		//	std::cout << "removed\n";
		}
		else {
			++it;
		}
	}
		

}

void SpawnEntity::draw(SDL_Renderer * renderer) const
{
	for (std::list<Entity *>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		(*it)->draw(renderer);
	}
}

bool SpawnEntity::message(MessageID id, void * data)
{
	
	if (id == MessageID::SCREEN_SIZE) {
		//Code here to handle the screen being resized.
		return true;
	}
	//Call to parent class.
	return Entity::message(id, data);
}
